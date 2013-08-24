#pragma once

#include "Constants.h"
#include "cocos2d.h"

enum GameOverType{
	PlayerLooseRock,
	PlayerLooseTime,
	PlayerWin
};

class GameOverLayer : public cocos2d::CCLayer
{
public:
	GameOverLayer(GameOverType type, CCObject *target, SEL_MenuHandler selector);

private:
	GameOverType type;

	void setupBackground();
	void setupLabel();
	void setupButton(CCObject *target, SEL_MenuHandler selector);

};
