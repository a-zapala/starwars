#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>
#include <type_traits>

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
    const U speed;
    const U attackPower;

public:
    using valueType = U;
    
    template<bool A = canAttack, typename = typename std::enable_if<A>::type>
    RebelStarship(U shield, const U speed, const U attackPower) : shield(shield), speed(speed),
                                                                  attackPower(attackPower) {
        assert(minSpeed <= speed);
        assert(maxSpeed >= speed);
    }
    
    template<bool A = canAttack, typename = typename std::enable_if<!A>::type>
    RebelStarship(U shield, const U speed) : shield(shield), speed(speed), attackPower(0) {
        assert(minSpeed <= speed);
        assert(maxSpeed >= speed);
    }
    
    U getShield() const {
        return shield;
    }
    
    U getSpeed() const {
        return speed;
    }
    
    void takeDamage(U damage) {
        if (shield > damage) {
            shield -= damage;
        }
        else {
            shield = 0;
        }
    }
    
    template<bool A = canAttack, typename = typename std::enable_if<A>::type>
    U getAttackPower() const {
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
