#include "Keyboard.h"	


Keyboard::Keyboard(){

}

Keyboard::~Keyboard(){

}

bool Keyboard::isKeyDown(InputKey key) const{
	return (s3eKeyboardGetState((s3eKey)key) & S3E_KEY_STATE_DOWN) == S3E_KEY_STATE_DOWN;
}

bool Keyboard::isKeyUp(InputKey key) const{
	return (s3eKeyboardGetState((s3eKey)key) & S3E_KEY_STATE_UP) == S3E_KEY_STATE_UP;
}


bool Keyboard::wasKeyPressed(InputKey key) const{
	return (s3eKeyboardGetState((s3eKey)key) & S3E_KEY_STATE_PRESSED) == S3E_KEY_STATE_PRESSED;
}


bool Keyboard::wasKeyReleased(InputKey key) const{
	return (s3eKeyboardGetState((s3eKey)key) & S3E_KEY_STATE_RELEASED) == S3E_KEY_STATE_RELEASED;
}
