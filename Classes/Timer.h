#pragma once

#include "Constants.h"

// LABEL BMF FONT
// Нужно чтобы показывал десятую долю серунды после точки?
class TimerSprite : public CCSprite{
public:
	TimerSprite(int seconds, int fontSize, ccColor3B color = ccc3(0,0,0));
	~TimerSprite();

	void setEndTimeCallback(CCObject *rec, SEL_MenuHandler selector);

	// default time is 1/10 of a second
	void setUpdateTime(float updateTime);
	void stop();

private:
	float currectSeconds;
	cocos2d::CCLabelTTF* timerLabel;

	CCObject *listener;
	SEL_MenuHandler selector;


	void setupLabel(int fontSize, ccColor3B color);
	void updateTime(float dt);
	std::string toString(float seconds);
};
