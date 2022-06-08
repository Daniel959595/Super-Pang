#include "CollisionHandling.h"

#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>


#include "Player.h"
#include "Level.h"
#include "RegularBall.h"




namespace // anonymous namespace — the standard way to make function "static"
{

    void ignore(GameObj& obg1,
        GameObj& obj2)
    {
        return;
    }
    // primary collision-processing functions
    void ballShot(GameObj& ball,
        GameObj& shot)
    {
        shot.setIsDisposed(true);
        ball.setIsDisposed(true);
        //Level::ballShot();
    }

 
    void shotBall(GameObj& shot,
        GameObj& ball)
    {
        ballShot(ball, shot);
    }
    

    using HitFunctionPtr = void (*)(GameObj&, GameObj&);
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(RegularBall), typeid(RegularShot))] = &ballShot;
        phm[Key(typeid(RegularShot), typeid(RegularBall))] = &shotBall;
        phm[Key(typeid(RegularShot), typeid(RegularShot))] = &ignore;
        phm[Key(typeid(RegularBall), typeid(RegularBall))] = &ignore;
        phm[Key(typeid(Player),      typeid(RegularBall))] = &ignore;  // currently!
        phm[Key(typeid(RegularBall), typeid(Player))]      = &ignore;  // currently!
        phm[Key(typeid(Player),      typeid(RegularShot))] = &ignore;  // currently!
        phm[Key(typeid(RegularShot), typeid(Player))]      = &ignore;  // currently!
        /*
        phm[Key(typeid(SpaceShip), typeid(SpaceShip))] = &shipShip;
        phm[Key(typeid(Asteroid), typeid(SpaceShip))] = &asteroidShip;
        phm[Key(typeid(SpaceStation), typeid(SpaceShip))] = &stationShip;
        phm[Key(typeid(SpaceStation), typeid(Asteroid))] = &stationAsteroid;*/
        
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));

    phf(object1, object2);
}
