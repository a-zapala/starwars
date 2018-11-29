#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>

namespace {
    constexpr int minSpeedExplorerAndXwing = 299796;
    constexpr int maxSpeedExplorerAndXwing = 2997960;
    constexpr int minSpeedStarCruiser = 99999;
    constexpr int maxSpeedStarCruiser = 299795;
}

template<typename U, int minSpeed, int maxSpeed, bool canAttack>
class RebelStarship {
private:
    U shield;
    U speed;
    const U attackPower;

public:
    using value_type = U;
    
    template<bool A = canAttack, typename = typename std::enable_if<A>::type>
    RebelStarship(U shield, const U speed, const U attackPower) : shield(shield), attackPower(attackPower),
                                                                  speed(speed) {
        assert(minSpeed <= speed);
        assert(maxSpeed >= speed);
    }
    
    template<bool A = canAttack, typename = typename std::enable_if<!A>::type>
    RebelStarship(U shield, const U speed) : shield(shield), speed(speed) , attackPower(0) {
        assert(minSpeed <= speed);
        assert(maxSpeed >= speed);
    }
    
    U getShield() {
        return shield;
    }
    
    U getSpeed() {
        return speed;
    }
    
    void takeDamage(U damage) {
        if (shield < damage) {
            shield -= damage;
        }
        else {
            shield = 0;
        }
    }
    
    template<bool A = canAttack, typename = typename std::enable_if<A>::type>
    U getAttackPower() {
        return attackPower;
    }
    
};

template<typename U>
using XWing = RebelStarship<U, minSpeedExplorerAndXwing, maxSpeedExplorerAndXwing, true>;
template<typename U>
using Explorer = RebelStarship<U, minSpeedExplorerAndXwing, maxSpeedExplorerAndXwing, false>;
template<typename U>
using StarCruiser = RebelStarship<U, minSpeedStarCruiser, maxSpeedStarCruiser, true>;

#endif //STARWARS_REBELFLEET_H
