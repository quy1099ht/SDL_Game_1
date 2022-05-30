#include <Entity.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(float p_x, float p_y, SDL_Texture* p_t)
:x(p_x), y(p_y) , currentTexture(p_t)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Entity::getX(){
	return x;
}
float Entity::getY(){
	return y;
}

SDL_Texture* Entity::getTex(){
	return currentTexture;
}

SDL_Rect Entity::getCurFrame(){
	return currentFrame;
}