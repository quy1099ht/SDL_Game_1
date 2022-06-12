#include <Entity.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Entity::Entity(Vector2f pos, SDL_Texture* p_t)
:position(pos), currentTexture(p_t)
{
	isFalling = true;
	isUp = false;
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

void Entity::setSize(int width,int height)
{
	currentFrame.w = width;
	currentFrame.h = height;
};

void Entity::setPosition(float x,float y){
	position = Vector2f(x,y);
};

void Entity::Falling(float speed){
	if(isFalling && !isUp){
		position.y += position.y * speed;
	}
};

void Entity::setFallingState(bool state){
	isFalling = state;
};

void Entity::moveVertical(int direction, float speed){
	if(direction == 1){
		//move right
		position.x += 1 * speed;
	}
	else if(direction == -1){
		//move left
		position.x -= 1 * speed;
	}
};

void Entity::setTempPlatform(Vector2f tmpPlatform){
	tempPlatform = tmpPlatform;
};

Vector2f Entity::getTempPlatform(){
	return tempPlatform;
};
void Entity::jumpUp(){
	isUp = true;
	position.x += 1;
	position.y = -2*(position.x * position.x) + 5 * position.x ;
}