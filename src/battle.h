#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <iostream>
#include <tuple>
#include <array>

#include "rebelfleet.h"
#include "imperialfleet.h"

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
public:
    SpaceBattle(S... ships) : ships(std::make_tuple(ships...)), currentTime(t0),
                              nextAttackIndex(firstTimeIndexAtack()) {
        static_assert(t0 <= t1, "Too big start time.");
        static_assert(t0 >= 0, "Start time lower than 0.");
        static_assert(t1 >= 0, "Max time lower than 0.");

        imperialFleetCount = 0;
        rebelFleetCount = 0;
        countTypeFleet(ships...);
    }

    size_t countImperialFleet() const {
        return imperialFleetCount;
    }

    size_t countRebelFleet() const {
        return rebelFleetCount;
    }

    void tick(T timeStep) {
        check_winner();

        if (squares[nextAttackIndex] == currentTime) {

            attackSequence(std::index_sequence_for<S...>());
        }
        currentTime = (currentTime + timeStep) % maxTime;
        countNextAtackIndex();
    }


private:
    std::tuple<S...> ships;
    static constexpr size_t shipsCount = sizeof...(S);
    T currentTime;
    T nextAttackIndex;
    static constexpr T maxTime = t1 + 1;
    size_t imperialFleetCount;
    size_t rebelFleetCount;

    template<typename U>
    struct isRebelStarshipS : std::false_type {
    };

    template<typename U, int minSpeed, int maxSpeed, bool canAttack>
    struct isRebelStarshipS<RebelStarship<U, minSpeed, maxSpeed, canAttack>> : std::true_type {
    };

    template<typename U>
    struct isImperialStarshipS : std::false_type {
    };

    template<typename U>
    struct isImperialStarshipS<ImperialStarship<U>> : std::true_type {
    };

    template<typename U>
    bool isRebelStarship(U) const {
        return isRebelStarshipS<U>::value;
    }

    template<typename U>
    bool isImperialStarship(U) const {
        return isImperialStarshipS<U>::value;
    }

    template<typename A>
    void countTypeFleet(A value) {
        if (isRebelStarship(value)) {
            rebelFleetCount++;
        } else if (isImperialStarship(value)) {
            imperialFleetCount++;
        }
    }

    template<typename A, typename... Args>
    void countTypeFleet(A first, Args... args) {
        if (isRebelStarship(first)) {
            rebelFleetCount++;
        } else if (isImperialStarship(first)) {
            imperialFleetCount++;
        }
        countTypeFleet(args...);
    }

    template<T limit>
    constexpr static T countLenSq() {
        T len{};
        for (len = 0; len * len < limit; ++len);
        return len;
    }

    template<T limit>
    constexpr static auto genSquares() {
        ::std::array<T, lenSquares> result{};
        for (T i = 0; (i == 0 && limit > 0) || i < limit / i; ++i)
            result[i] = i * i;
        return result;
    }

    constexpr static T lenSquares = countLenSq<maxTime>();
    constexpr static auto squares = genSquares<maxTime>();

    constexpr static T firstTimeIndexAtack() {
        for (T i = 0; i < lenSquares; ++i) {
            if (squares[i] >= t0) {
                return i;
            }
        }
        return 0;
    }

    void countNextAtackIndex() {
        if(squares[nextAttackIndex] > currentTime)
            nextAttackIndex = 0;

        for (; nextAttackIndex < lenSquares; ++nextAttackIndex) {
            if (squares[nextAttackIndex] >= currentTime) {
                return;
            }
        }
        nextAttackIndex = 0;
    }

    template<typename I>
    bool isAlive(I& ship) {
        return ship.getShield() > 0;
    }

    template<typename U, int minSpeed, int maxSpeed, bool canAttack>
    void attackSequenceImperial(RebelStarship<U, minSpeed, maxSpeed, canAttack> &) {}

    template<typename U>
    void attackSequenceImperial(ImperialStarship<U> &first) {
        if (isAlive(first)) attackSequenceR(first, std::index_sequence_for<S...>());
    }

    template<typename U, int minSpeed, int maxSpeed, bool canAttack, typename... Args>
    void attackSequenceImperial(RebelStarship<U, minSpeed, maxSpeed, canAttack> &, Args &... base) {
        attackSequenceImperial(base...);
    }

    template<typename U, typename... Args>
    void attackSequenceImperial(ImperialStarship<U> &first, Args &... base) {
        if (isAlive(first)) {
            attackSequenceR(first, std::index_sequence_for<S...>());
        }
        attackSequenceImperial(base...);
    }

    template<typename I, typename U>
    void attackSequenceRebel(ImperialStarship<I> &, ImperialStarship<U> &) {}

    template<typename I, typename U, int minSpeed, int maxSpeed, bool canAttack>
    void
    attackSequenceRebel(ImperialStarship<I> &imperialShip, RebelStarship<U, minSpeed, maxSpeed, canAttack> &first) {
        if (isAlive(imperialShip) && isAlive(first)) {
            attack(imperialShip, first);
            if (!isAlive(imperialShip)) imperialFleetCount--;
            if (!isAlive(first)) rebelFleetCount--;
        }
    }

    template<typename I, typename U, typename... Args>
    void attackSequenceRebel(ImperialStarship<I> &imperialShip, ImperialStarship<U> &, Args &... base) {
        if (!isAlive(imperialShip)) return;
        attackSequenceRebel(imperialShip, base...);
    }

    template<typename I, typename U, int minSpeed, int maxSpeed, bool canAttack, typename... Args>
    void attackSequenceRebel(ImperialStarship<I> &imperialShip,
                             RebelStarship<U, minSpeed, maxSpeed, canAttack> &first, Args &... base) {
        if (!isAlive(imperialShip)) return;
        if (isAlive(first)) {
            attack(imperialShip, first);
            if (!isAlive(imperialShip)) imperialFleetCount--;
            if (!isAlive(first)) rebelFleetCount--;
        }
        attackSequenceRebel(imperialShip, base...);
    }

    template<size_t... Is>
    void attackSequence(std::index_sequence<Is...>) {
        attackSequenceImperial(std::get<Is>(ships)...);
    }

    template<typename U, size_t... Is>
    void attackSequenceR(ImperialStarship<U> &imperialShip, std::index_sequence<Is...>) {
        attackSequenceRebel(imperialShip, std::get<Is>(ships)...);
    }

    void check_winner() const {
        if (countImperialFleet() == 0 && countRebelFleet() == 0) {
            std::cout << "DRAW" << std::endl;
        } else if (countRebelFleet() == 0) {
            std::cout << "IMPERIUM WON" << std::endl;
        } else if (countImperialFleet() == 0) {
            std::cout << "REBELLION WON" << std::endl;
        }
    }

};

#endif //STARWARS_BATTLE_H
