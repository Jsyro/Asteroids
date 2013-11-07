#pragma once

#include "resource.h"

#define SCREEN_WIDTH	 1200
#define SCREEN_HEIGHT	  675
#define SHIP_RAD		   30
#define	FRAME_TIME		   16

#define FORWARD			VK_UP
#define SPIN_LEFT		VK_LEFT
#define SPIN_RIGHT		VK_RIGHT
#define KEY_SHOOT		VK_SPACE

#define XWRAP			SCREEN_WIDTH-18
#define YWRAP			SCREEN_HEIGHT-54
#define SPIN_SPEED		(float)(5*(3.14/180))
#define ACC_SPEED		(float)0.5
#define VEL_MAX			30
#define BULLET_SPEED	12
#define BULLET_SIZE		4
#define MAX_BULLETS		15
#define DRAG			(float)0.985
#define TIMER_ID		140

