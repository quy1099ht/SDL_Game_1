#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>

#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <Utils.hpp>

int main(int argc, char *args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init failed . Error : " << SDL_GetError() << std::endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_Init has failed" << SDL_GetError() << std::endl;
	}

	RenderWindow window("GAME v0.1", 1280, 720);

	// int windowRefreshRate = window.getRefreshRate();

	std::cout << "Frame rate = " << window.getRefreshRate() << std::endl;

	SDL_Texture *grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	SDL_Texture *platformTexture = window.loadTexture("res/gfx/platform.png");
	SDL_Texture *playerTexture = window.loadTexture("res/gfx/player.png");

	std::vector<Entity> entities;
	std::vector<Entity> platforms;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	int range = 300 - 100 + 1;
	Entity player(Vector2f(0, 100), playerTexture);
	for (int i = 0; i < 20; i++)
	{
		int num = rand() % range + 100;
		Entity platform(Vector2f(i * 64, 600), platformTexture);
		platform.setSize(64, 32);
		platforms.push_back(platform);
	}

	utils::logNumber("Player x pos", player.getPosition().x);
	utils::logNumber("Player y pos", player.getPosition().y);
	utils::logNumber("First platform pos x", platforms[0].getPosition().x);
	utils::logNumber("First platform pos y", platforms[0].getPosition().y);

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Opimize CPU running
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		int startTicks = SDL_GetTicks();

		currentTime = newTime;

		accumulator += frameTime;
		// All these above is for not overloading CPU

		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						utils::logTexts("Press btn", "w");
						break;
					case SDLK_LEFT:
						utils::logTexts("Press btn", "left arrow");
						player.moveVertical(-1);
						break;
					case SDLK_RIGHT :
						utils::logTexts("Press btn", "right arrow");
						player.moveVertical(1);
						break;
					default:
						break;
					}
				}
			}
			accumulator -= timeStep;
		}

		/* code */
		// const float alpha = accumulator / timeStep;

		window.clear();
		// Game rendering loop
		player.Falling(0.005f);

		// Render entities
		window.render(player);

		for (Entity &platform : platforms)
		{
			window.render(platform);
		}

		if (utils::distanceFrom2Object(player.getPosition(), platforms[0].getPosition()) < 34)
		{
			player.setFallingState(false);
		}

		// utils::logTime();

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < (1000 / window.getRefreshRate()))
		{
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	};

	window.cleanUp();
	SDL_Quit();

	return 0;
};