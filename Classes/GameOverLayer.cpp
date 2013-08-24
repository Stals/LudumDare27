#include "GameOverLayer.h"

GameOverLayer::GameOverLayer(GameOverType type): type(type){
	CCLayer::init();
	this->setTouchEnabled(true);
	setupBackground();
	setupLabel();
	setupButton();
}

void GameOverLayer::setupBackground(){
	this->addChild(CCLayerColor::create(ccc4(0, 0, 0, 200)));
}

void GameOverLayer::setupLabel(){
	std::string message;

	switch(type){
	case PlayerLooseRock:
		message = "You were killed by a rock";
		break;

	case PlayerLooseTime:
		message = "              Time is up!\nThere is no way to escape now";
		break;

	case PlayerWin:
		message = "      Congtatulations!\nYou managed to survive";
		break;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::create(message.c_str(), "arial", 25);
	label->setColor(ccc3(255, 255, 255));

	label->setPosition(ccp(winSize.width/2, (winSize.height/2) + 100));

	this->addChild(label);
}

void GameOverLayer::setupButton(){

}
