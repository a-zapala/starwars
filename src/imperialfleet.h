#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

namespace {
    enum ShipType {
        DEATH_STAR = 0,
        IMPERIAL_DESTROYER = 1,
        TIE_FIGHTER = 2
    };
}

template <typename U, ShipType T>
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

template <typename U> using DeathStar = ImperialStarship<U, DEATH_STAR>;
template <typename U> using ImperialDestroyer = ImperialStarship<U, IMPERIAL_DESTROYER>;
template <typename U> using TIEFighter = ImperialStarship<U, TIE_FIGHTER>;


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
