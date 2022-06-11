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
	void setPosition(float x, float y);
private:
	Vector2f position;
	SDL_Rect currentFrame;
	SDL_Texture * currentTexture;
};