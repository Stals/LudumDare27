#include "GameOverLayer.h"

GameOverLayer::GameOverLayer(GameOverType type, CCObject *target, SEL_MenuHandler onePlayer, SEL_MenuHandler twoPlayers): type(type){
	CCLayer::init();
	this->setTouchEnabled(true);
	setupBackground();
	setupLabel();
	setupTitle();
	setupButton(target, onePlayer, twoPlayers);
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
	CCLabelTTF* label = CCLabelTTF::create(message.c_str(), "fonts/Quicksand_Bold", 25);
	label->setColor(ccc3(255, 255, 255));

	label->setPosition(ccp(winSize.width/2, (winSize.height/2) + 175));

	this->addChild(label);
}

void GameOverLayer::setupButton(CCObject *target, SEL_MenuHandler onePlayer, SEL_MenuHandler twoPlayers){
	CCSprite *onePlayerUnselected = CCSprite::create("1Player_unselected.png");
	CCSprite *onePlayerSelected = CCSprite::create("1Player_selected.png");
	CCMenuItemSprite *onePlayerButton = CCMenuItemSprite::create(onePlayerUnselected, onePlayerSelected, onePlayerUnselected,
		target, onePlayer);


	CCSprite *twoPlayerUnselected = CCSprite::create("2Players_unselected.png");
	CCSprite *twoPlayerSelected = CCSprite::create("2Players_selected.png");
	CCMenuItemSprite *twoPlayerButton = CCMenuItemSprite::create(twoPlayerUnselected, twoPlayerSelected, twoPlayerUnselected,
		target, twoPlayers);

	CCMenu* menu = CCMenu::create(onePlayerButton, twoPlayerButton, NULL);


	menu->alignItemsHorizontallyWithPadding(20);


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// Set position of menu to be below the title text
	menu->setPosition(ccp(winSize.width/2, (winSize.height/2)));

	// Add menu to layer
	this->addChild(menu, 2);
}

void GameOverLayer::setupTitle(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *title = CCSprite::create("Title.png");
	title->setPosition(ccp(winSize.width/2, winSize.height/2));

	this->addChild(title, 0);
}
