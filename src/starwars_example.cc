#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>
#include <type_traits>

int main() {
    XWing<float> xwing(100.0f, 300000.0f, 50.0f);
    Explorer<int> explorer(150, 400000);
    StarCruiser<unsigned> cruiser(1234, 100000, 11);
    DeathStar<long> deathStar(10000, 75);
    TIEFighter<unsigned> fighter(50, 9);
    ImperialDestroyer<int> destroyer(150, 20);


    attack(deathStar, explorer);
    assert(deathStar.getShield() == 10000);
    assert(explorer.getShield() == 75);

    attack(fighter, xwing);
    assert(fighter.getShield() == 0);
    assert(xwing.getShield() == 91);

    attack(destroyer, cruiser);
    assert(destroyer.getShield() == 139);
    assert(cruiser.getShield() == 1214);


    auto battle = SpaceBattle<short, 1, 23,
                              DeathStar<long>,
                              Explorer<int>,
                              TIEFighter<unsigned>,
                              XWing<float>>(deathStar,
                                            explorer,
                                            fighter,
                                            xwing);

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);
//
//    battle.tick(2);
//    assert(battle.countRebelFleet() == 2);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(1);
//    assert(battle.countRebelFleet() == 2);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(4);
//    assert(battle.countRebelFleet() == 0);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}
