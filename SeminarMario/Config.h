#pragma once

#define  SCREE�_HEIGHT 745
#define  SCREEN_WIDTH 1370
#define DEFAULT_HERO_X 0
#define DEFAULT_HERO_Y 600
#define DEFAULT_SILME_Y 583.58
#define DEFAULT_LIVES_X 1301.5
#define DEFAULT_LIVES_Y 43.82
#define DEFAULT_SCORE_X 91.3
#define DEFAULT_SCORE_Y 74.5

#include "EntitiesPool.h"




enum EventSenders { SENDER_ENTITY_STATE, SENDER_KEYBOARD, SENDER_TIMER };
enum EventTypes { EVENT_KEY_PRESSED, EVENT_PHYSICS, EVENT_GRAPHICS, EVENT_TIMER };
enum EventCodes {
	ENTITY_PHYSICS_FINISHED,
	ENTITY_GRAPHICS_FINISHED,
	TIME_TICK,
	KEY_ESC = 27,
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_DOWN = 's',
	KEY_UP = 'w',
	COLLISION_WITH_ENEMY,
	COLLISION_WITH_FOOD_LIFE,
	COLLISION_WITH_FOOD_SCORE,
};

