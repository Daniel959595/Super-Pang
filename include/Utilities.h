#pragma once

#include "sfml/Graphics.hpp"

#include "Direction.h"
#include "Resources.h"

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50

#define BACBGROUND_WIDTH 1400
#define BACBGROUND_HEIGHT 900

#define NUM_LEVELS 1


enum class ButtonType {
	START = 0,
	HELP,
	SCORE,
	EXIT,
};