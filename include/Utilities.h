#pragma once

#include "sfml/Graphics.hpp"

#include "Direction.h"
#include "Resources.h"

#define NUM_LEVELS 1

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 1000

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50

#define BACBGROUND_WIDTH 1400
#define BACBGROUND_HEIGHT 900

#define TABLE_WIDTH 1370
#define TABLE_HEIGHT 830

#define FRAME_WIDTH 35

#define BIG_BALL_SIZE 170
#define MEDIUM_BALL_SIZE 140



enum class ButtonType {
	START = 0,
	HELP,
	SCORE,
	EXIT,
};

enum class BallSize {
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