#pragma once

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace cocos2d;

#define PTM_RATIO 32.0f

enum zOrder{
	zBackground,
	zGround,
	zFinish,
	zRock,
	zPlayer,
	zGameOver
};
