#include "Timer.h"

#include <sstream>

TimerSprite::TimerSprite(int seconds, int fontSize, ccColor3B color){
	CCSprite::init();

	currectSeconds = seconds;
	
	this->setupLabel(fontSize, color);

	this->setUpdateTime(0.1f);
}

TimerSprite::~TimerSprite(){
}

void TimerSprite::setupLabel(int fontSize, ccColor3B color){ //Quicksand_Bold
	timerLabel = CCLabelTTF::create(toString(currectSeconds).c_str(), "fonts/Quicksand_Bold", fontSize, CCSizeMake(200,200), cocos2d::CCTextAlignment::kCCTextAlignmentCenter);
	timerLabel->setColor(color);
	timerLabel->setOpacity(127);
	timerLabel->setAnchorPoint(ccp(0.5,0.5));
	timerLabel->setPositionX(50);
	this->addChild(timerLabel);
	
	
}

void TimerSprite::setUpdateTime(float updateTime){
	this->schedule(schedule_selector(TimerSprite::updateTime), updateTime);
}

void TimerSprite::updateTime(float dt){
	currectSeconds -= 0.1f;
	timerLabel->setString(toString(currectSeconds).c_str());
}


std::string TimerSprite::toString(float seconds){
	static char cVal[4];
	sprintf(cVal,"%.1f",seconds); 
	return cVal;
}
