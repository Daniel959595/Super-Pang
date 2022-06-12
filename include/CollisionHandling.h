#pragma once

#include "GameObj.h"
//#include "Level.h"

#include <typeinfo>
#include <typeindex>

class Level;

class CollisionHandling
{
public:

    using HitFunctionPtr = void (CollisionHandling::*)(GameObj&, GameObj&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    CollisionHandling(Level& gameLevel);
    void processCollision(GameObj& object1, GameObj& object2);
    HitMap initializeCollisionMap();
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);

private:
    void ignore           (GameObj& obg1,     GameObj& obj2);
    void ballShot         (GameObj& baseBall, GameObj& baseShot);
    void shotBall         (GameObj& baseShot, GameObj& baseBall);
    void ballBreakableTile(GameObj& baseBall, GameObj& Tile);
    void BreakableTileBall(GameObj& Tile,     GameObj& baseBall);
    
    void shotBreakableTile(GameObj& shot, GameObj& tile);
    void breakableTileShot(GameObj& tile, GameObj& shot);

private:
    Level& m_gameLevel;
};

