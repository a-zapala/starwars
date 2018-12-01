#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <iostream>
#include <tuple>

#include "rebelfleet.h"
#include "imperialfleet.h"

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
public:
    
    SpaceBattle(S... ships) : ships(std::make_tuple(ships...)), currentTime(t0) {
        static_assert(t0 < t1, "Too big start time.");
        static_assert(t0 >= 0, "Start time lower than 0.");
        static_assert(t1 >= 0, "Max time lower than 0.");
        
        imperialFleetCount = 0;
        rebelFleetCount = 0;
        countTypeFleet(ships...);
        
//        !!!!!!!!!!!!!!!!!!! Nie działa, bo do tuple jest dostęp tylko ze stałymi indeksami. !!!!!!!!!!!!!!!!!!!!!!!!
//        !!!!!!!!!!!!!!!!! Ale dobrze sprawdza, czy statek jest statkiem rebelii, czy imperium. !!!!!!!!!!!!!!!!!!!!!
//        for (size_t i = 0; i < shipsCount; i++) {
//            if (isRebelStarship(std::get<i>(this->ships))) {
//                rebelFleetCount++;
//            } else if (isImperialStarship(std::get<i>(this->ships))) {
//                imperialFleetCount++;
//            }
//        }

//        !!!!!!!!!!!!!!!!!!!!!!!! Takie coś działa !!!!!!!!!!!!!!!!!!!!!!!
//        if (isRebelStarship(std::get<2>(this->ships))) {
//            rebelFleetCount++;
//        } else if (isImperialStarship(std::get<2>(this->ships))) {
//            imperialFleetCount++;
//        }
    }
    
    template<typename A>
    void countTypeFleet(A value) {
        if (isRebelStarship(value)) {
            rebelFleetCount++;
        }
        else if (isImperialStarship(value)) {
            imperialFleetCount++;
        }
    }
    
    template<typename A, typename... Args>
    void countTypeFleet(A first, Args... args) {
        if (isRebelStarship(first)) {
            rebelFleetCount++;
        }
        else if (isImperialStarship(first)) {
            imperialFleetCount++;
        }
        countTypeFleet(args...);
    }
    
    size_t countImperialFleet() {
        return imperialFleetCount;
    }
    
    size_t countRebelFleet() {
        return rebelFleetCount;
    }
    
    void tick(T timeStep) {
    
    }

private:
    std::tuple<S...> ships;
    static constexpr size_t shipsCount = sizeof...(S);
    T currentTime;
    static constexpr T maxTime = t1;
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
    bool isRebelStarship(U) {
        return isRebelStarshipS<U>::value;
    }
    
    template<typename U>
    bool isImperialStarship(U) {
        return isImperialStarshipS<U>::value;
    }
};

#endif //STARWARS_BATTLE_H
