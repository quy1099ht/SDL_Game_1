#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Math.hpp>

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
 	Vector2f& getPosition(){
 		return position;
 	};
	SDL_Texture * getTex();
	SDL_Rect getCurFrame();
	void setFallingState(bool state);
	void setPosition(float x, float y);
	void setSize(int width , int height);
	void Falling(float speed);
	void moveVertical(int direction, float speed);
	void moveHorizontal();
	void setTempPlatform(Vector2f tmpPlatform);
	Vector2f getTempPlatform();
	void jumpUp();
	void setIsUp(bool state);
	bool getIsUp();
private:
	Vector2f position;
	SDL_Rect currentFrame;
	SDL_Texture * currentTexture;
	Vector2f tempPlatform;
	bool isFalling; 
	bool isUp;
	char* tag;
};