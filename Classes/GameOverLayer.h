#pragma once

#include "Constants.h"
#include "cocos2d.h"

enum GameOverType{
	PlayerLooseRock,
	PlayerLooseTime,
	PlayerWin,
	None
};

class GameOverLayer : public cocos2d::CCLayer
{
public:
	GameOverLayer(GameOverType type, CCObject *target, SEL_MenuHandler onePlayer, SEL_MenuHandler twoPlayers);

private:
	GameOverType type;

	void setupBackground();
	void setupLabel();
	void setupTitle();
	void setupButton(CCObject *target, SEL_MenuHandler onePlayer, SEL_MenuHandler twoPlayers);

};
