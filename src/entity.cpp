#include <Entity.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Entity::Entity(Vector2f pos, SDL_Texture* p_t)
:position(pos), currentTexture(p_t)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

SDL_Texture* Entity::getTex(){
	return currentTexture;
}

SDL_Rect Entity::getCurFrame(){
	return currentFrame;
}



void Entity::setPosition(float x,float y){
	position = Vector2f(x,y);
}