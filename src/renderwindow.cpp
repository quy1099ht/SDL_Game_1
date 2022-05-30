#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <RenderWindow.hpp>

RenderWindow::RenderWindow(const char* p_title,int p_w,int p_h)
:window(NULL), renderer(NULL)
{
	//SDL_CreateWindow(<window title>, <x position on screen>, <y position on screen>,<width>, <height>, true || false => show window????)
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);
	if(window == NULL){
		std::cout << "Window failed to init" << SDL_GetError() << std::endl;
	}

	//SDL_CreateRenderer(<window (from SDL_CreateWindow)>, -1 <I forgot what it is>, <for handling graphic card>)
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUp(){
	SDL_DestroyWindow(window);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer,p_filePath);
	if(texture == NULL)
	{
		std::cout << "Failed to load texture. Error : " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex){
	SDL_RenderCopy(renderer,p_tex,NULL,NULL);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}