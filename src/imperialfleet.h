#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

template <typename U>
class ImperialStarship {
public:
    using valueType = U;

    ImperialStarship(U shield, const U attackPower) : shield(shield), attackPower(attackPower) {}

    U getShield() {
        return shield;
    }

    U getAttackPower() {
        return attackPower;
    }

    void takeDamage(U damage) {
        if (damage > shield) {
            shield = 0;
        } else {
            shield -= damage;
        }
    }
private:
    U shield;
    const U attackPower;
};

template <typename U> using DeathStar = ImperialStarship<U>;
template <typename U> using ImperialDestroyer = ImperialStarship<U>;
template <typename U> using TIEFighter = ImperialStarship<U>;


template <typename I, typename R> void attack(I& imperialShip, R& rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template <typename I, typename T> void attack(I& imperialShip, StarCruiser<T>& rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template <typename I, typename T> void attack(I& imperialShip, XWing<T>& rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

#endif //STARWARS_IMPERIALFLEET_H
