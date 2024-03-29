#pragma once

#include "sfml/Graphics.hpp"
#include <SFML/Audio.hpp>

#include "Direction.h"
#include "Direction.h"
#include "Resources.h"
#include "Sounds.h"

#define NUM_LEVELS 2

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 1000

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 80

#define BACBGROUND_WIDTH 1400
#define BACBGROUND_HEIGHT 900

#define FRAME_WIDTH 35

#define TABLE_WIDTH 1370
#define TABLE_HEIGHT 830

// in the png file!!! 
#define PLAYER_WIDTH  32
#define PLAYER_HIEGHT 32

#define DEFAULT_LIFE 6

#define BIG_BALL_SIZE    170
#define MEDIUM_BALL_SIZE 140
#define SMALL_BALL_SIZE  110


#define BIG_BALL_SIZE    170
#define MEDIUM_BALL_SIZE 140
#define SMALL_BALL_SIZE  110
#define TINY_BALL_SIZE    60


#define BIG_TILE_SIZE    170
#define MEDIUM_TILE_SIZE 140
#define SMALL_TILE_SIZE  110
#define TINY_TILE_SIZE   110

// final size.
#define GIFT_SIZE        60

#define GIFT_SCORE       10

#define VOLUME           50
#define NUM_MUSICS        3
#define NUM_GIFTS         3

enum class Situation
{
	//GameBegan,
	LevelRunnig,
	LevelSucced,
	LevelFailed,
	GameOver,
	GameFinished,
	EscKeyPressed,
};

enum class MixDirection {
	UpAndLeft = 0,
	UpAndRight,
	DownAndLeft,
	DownAndRight,
	Up,
	Down, 
	Right,
	Left,
	Unkown, // 
};

enum class TileCorner {
	UpRight,
	UpLeft,
	DownLeft,
	DownRight,
	Middle,
};

enum class ButtonType {
	START = 0,
	HELP,
	SCORE,
	EXIT,
};

enum class GiftType {
	ScoreGift,
	ShotsGift,
	ExtraLifeGift,
};

enum class BallSize {
	Big,
	Medium,
	Small,
	Tiny,
};

enum class TileSize {
	Big,
	Medium,
	Small,
};

enum class ShotType {
	Normal,
	Double,
	Special,
	Bullets,
};

enum class TileColor {
	Red,
	Blue,
	Orange,
};

