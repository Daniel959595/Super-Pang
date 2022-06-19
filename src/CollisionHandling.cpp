#include "CollisionHandling.h"

#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>


#include "Player.h"
#include "Level.h"
#include "RegularBall.h"
#include "TriangleBall.h"
#include "RegularShot.h"
#include "BreakableTile.h"
#include "BaseGift.h"
#include "ScoreGift.h"
#include "ShotGift.h"
#include "LifeGift.h"
//#include "Gift.h"



CollisionHandling::CollisionHandling(Level& gameLevel)
    : m_gameLevel(gameLevel)
{
}

void CollisionHandling::ignore(GameObj& obg1, GameObj& obj2)
{
    return;
}

void CollisionHandling::ballShot(GameObj& baseBall, GameObj& baseShot)
{
    baseShot.setIsDisposed(true);
    baseBall.setIsDisposed(true);
    baseBall.activateSound(Sounds::Sound::BallExplosion);
}

void CollisionHandling::shotBall(GameObj& baseshot, GameObj& baseBall)
{
    ballShot(baseBall, baseshot);
}
   
void CollisionHandling::ballBreakableTile(GameObj& baseBall, GameObj& Tile)
{
    /*BaseBall& ball      = dynamic_cast<BaseBall&>(baseBall);
    BreakableTile& tile = dynamic_cast<BreakableTile&>(Tile);*/

    //ball.analizeCollision(Tile);
    //ball.fixCollision(tile);
    //tile.setIsDisposed(true);
}

void CollisionHandling::BreakableTileBall(GameObj& Tile, GameObj& baseBall)
{
    /*ballBreakableTile(baseBall, Tile);*/
}

void CollisionHandling::shotBreakableTile(GameObj& shot, GameObj& tile)
{
    shot.setIsDisposed(true);
    tile.setIsDisposed(true);
    tile.activateSound(Sounds::Sound::TileBreaking);
}

void CollisionHandling::breakableTileShot(GameObj& tile, GameObj& shot)
{
    shotBreakableTile(shot, tile);
}

void CollisionHandling::playerBall(GameObj& player, GameObj& ball)
{
    Player& gamePlayer = dynamic_cast<Player&>(player);
    BaseBall& gameBall = dynamic_cast<BaseBall&>(ball);

    if (gameBall.isCollide()) {
        gamePlayer.removeLife();
        gamePlayer.setIsDisposed(true);
        gamePlayer.activateSound(Sounds::Sound::Faild);
    }
}

void CollisionHandling::ballPlayer(GameObj& ball, GameObj& player)
{
    playerBall(player, ball);
}

void CollisionHandling::playerGift(GameObj& player, GameObj& gift)
{
    Player& gamePlayer = dynamic_cast<Player&>(player);
    BaseGift& gameGift = dynamic_cast<BaseGift&>(gift);

    gamePlayer.activateGift(gameGift.getGiftType());

    gameGift.setIsDisposed(true);
}

void CollisionHandling::giftPlayer(GameObj& gift, GameObj& player)
{
    playerGift(player, gift);
}

void CollisionHandling::giftTile(GameObj& gift, GameObj& tile)
{
    BaseGift& gameGift = dynamic_cast<BaseGift&>(gift);

    gameGift.fixCollision(tile);
}

void CollisionHandling::tileGift(GameObj& tile, GameObj& gift)
{
    giftTile(gift, tile);
}


CollisionHandling::HitMap CollisionHandling::initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(RegularBall),   typeid(RegularShot))]   = &CollisionHandling::ballShot;
    phm[Key(typeid(RegularShot),   typeid(RegularBall))]   = &CollisionHandling::shotBall;
    phm[Key(typeid(RegularShot),   typeid(RegularShot))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularBall),   typeid(RegularBall))]   = &CollisionHandling::ignore;
    phm[Key(typeid(Player),        typeid(RegularBall))]   = &CollisionHandling::playerBall;  
    phm[Key(typeid(RegularBall),   typeid(Player))]        = &CollisionHandling::ballPlayer;  

    phm[Key(typeid(TriangleBall),  typeid(RegularShot))]   = &CollisionHandling::ballShot;
    phm[Key(typeid(RegularShot),   typeid(TriangleBall))]  = &CollisionHandling::shotBall;
    phm[Key(typeid(TriangleBall),  typeid(TriangleBall))]  = &CollisionHandling::ignore;
    phm[Key(typeid(Player),        typeid(TriangleBall))]  = &CollisionHandling::playerBall;
    phm[Key(typeid(TriangleBall),  typeid(Player))]        = &CollisionHandling::ballPlayer;
    phm[Key(typeid(ScoreGift),     typeid(TriangleBall))]  = &CollisionHandling::ignore;
    phm[Key(typeid(TriangleBall),  typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(TriangleBall),  typeid(BreakableTile))] = &CollisionHandling::ballBreakableTile;
    phm[Key(typeid(BreakableTile), typeid(TriangleBall))]  = &CollisionHandling::BreakableTileBall;

    phm[Key(typeid(Player),        typeid(RegularShot))]   = &CollisionHandling::ignore;  
    phm[Key(typeid(RegularShot),   typeid(Player))]        = &CollisionHandling::ignore;  

    phm[Key(typeid(BreakableTile), typeid(Player))]        = &CollisionHandling::ignore;  // currently!
    phm[Key(typeid(Player),        typeid(BreakableTile))] = &CollisionHandling::ignore;  // currently!
    phm[Key(typeid(RegularBall),   typeid(BreakableTile))] = &CollisionHandling::ballBreakableTile; 
    phm[Key(typeid(BreakableTile), typeid(RegularBall))]   = &CollisionHandling::BreakableTileBall;  

    phm[Key(typeid(RegularShot),   typeid(BreakableTile))] = &CollisionHandling::shotBreakableTile;
    phm[Key(typeid(BreakableTile), typeid(RegularShot))]   = &CollisionHandling::breakableTileShot;
    
    phm[Key(typeid(ScoreGift),     typeid(RegularShot))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularShot),   typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(ScoreGift),     typeid(TriangleBall))]  = &CollisionHandling::ignore;
    phm[Key(typeid(TriangleBall),  typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(ScoreGift),     typeid(RegularBall))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularBall),   typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(Player),        typeid(ScoreGift))]     = &CollisionHandling::playerGift;
    phm[Key(typeid(ScoreGift),     typeid(Player))]        = &CollisionHandling::giftPlayer;
    phm[Key(typeid(ScoreGift),     typeid(BreakableTile))] = &CollisionHandling::giftTile;
    phm[Key(typeid(BreakableTile), typeid(ScoreGift))]     = &CollisionHandling::tileGift;
    phm[Key(typeid(ScoreGift),     typeid(ScoreGift))]     = &CollisionHandling::ignore;

    phm[Key(typeid(LifeGift),      typeid(RegularShot))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularShot),   typeid(LifeGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(LifeGift),      typeid(TriangleBall))]  = &CollisionHandling::ignore;
    phm[Key(typeid(TriangleBall),  typeid(LifeGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(LifeGift),      typeid(RegularBall))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularBall),   typeid(LifeGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(Player),        typeid(LifeGift))]      = &CollisionHandling::playerGift;
    phm[Key(typeid(LifeGift),      typeid(Player))]        = &CollisionHandling::giftPlayer;
    phm[Key(typeid(LifeGift),      typeid(BreakableTile))] = &CollisionHandling::giftTile;
    phm[Key(typeid(BreakableTile), typeid(LifeGift))]      = &CollisionHandling::tileGift;
    phm[Key(typeid(LifeGift),      typeid(LifeGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(LifeGift),      typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(ScoreGift),     typeid(LifeGift))]      = &CollisionHandling::ignore;

    phm[Key(typeid(ShotGift),      typeid(RegularShot))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularShot),   typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(ShotGift),      typeid(TriangleBall))]  = &CollisionHandling::ignore;
    phm[Key(typeid(TriangleBall),  typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(ShotGift),      typeid(RegularBall))]   = &CollisionHandling::ignore;
    phm[Key(typeid(RegularBall),   typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(Player),        typeid(ShotGift))]      = &CollisionHandling::playerGift;
    phm[Key(typeid(ShotGift),      typeid(Player))]        = &CollisionHandling::giftPlayer;
    phm[Key(typeid(ShotGift),      typeid(BreakableTile))] = &CollisionHandling::giftTile;
    phm[Key(typeid(BreakableTile), typeid(ShotGift))]      = &CollisionHandling::tileGift;
    phm[Key(typeid(ShotGift),      typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(ShotGift),      typeid(ScoreGift))]     = &CollisionHandling::ignore;
    phm[Key(typeid(ScoreGift),     typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(ShotGift),      typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(LifeGift),      typeid(ShotGift))]      = &CollisionHandling::ignore;
    phm[Key(typeid(ShotGift),      typeid(LifeGift))]      = &CollisionHandling::ignore;

        
    return phm;
}

CollisionHandling::HitFunctionPtr CollisionHandling::lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

void CollisionHandling::processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));

    (this->*phf)(object1, object2);
}
