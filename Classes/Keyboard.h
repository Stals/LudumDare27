#pragma once
#include "s3eKeyboard.h"

enum InputKey{
	Key_Left = s3eKeyAbsLeft,
	Key_Right = s3eKeyAbsRight,
	Key_Up = s3eKeyAbsUp,
	Key_Down = s3eKeyAbsDown,
	Key_Space = s3eKeySpace 
};

class Keyboard{
public:
	Keyboard();
	~Keyboard();

	bool isKeyDown(InputKey key) const;
	bool isKeyUp(InputKey key) const;

	// return true if key was just pressed
	bool wasKeyPressed(InputKey key) const;
	// return true if key was just released
	bool wasKeyReleased(InputKey key) const;
};
