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

	SDL_Texture *platformTexture = window.loadTexture("res/gfx/platform.png");
	SDL_Texture *playerTexture = window.loadTexture("res/gfx/player.png");
	
	

	std::vector<Entity> entities;
	std::vector<Entity> platforms;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	int range = 300 - 100 + 1;
	Entity player(Vector2f(0, 100), playerTexture);
	player.setTempPlatform(Vector2f(-1, -1));
	for (int i = 0; i < 40; i++)
	{
		int num = rand() % range + 100;
		Entity platform(Vector2f(i * 32, 600 - num), platformTexture);
		platform.setSize(32, 32);
		platforms.push_back(platform);
	}

	utils::logNumber("Player x pos", player.getPosition().x);
	utils::logNumber("Player y pos", player.getPosition().y);
	utils::logNumber("First platform pos x", platforms[0].getPosition().x);
	utils::logNumber("First platform pos y", platforms[0].getPosition().y);

	bool gameRunning = true;

	SDL_Event event;
	int jumpFrame = 0;
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
			// Handle input
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
						break;
					case SDLK_UP:
						player.setIsUp(true);
						break;
					case SDLK_LEFT:
						player.moveVertical(-1, 2);
						break;
					case SDLK_RIGHT:
						player.moveVertical(1, 2);
						break;
					default:
						break;
					}
				}
				else if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						break;
					case SDLK_UP:
						break;
					case SDLK_LEFT:

						break;
					case SDLK_RIGHT:

						break;
					default:
						break;
					}
				}
			}
			accumulator -= timeStep;
		}

		if (jumpFrame > 100)
		{
			player.setIsUp(false);
			jumpFrame = 0;
		}

		if (player.getIsUp())
		{
			jumpFrame++;
			player.jumpUp();
		}

		window.clear();
		// Game rendering loop
		player.Falling(0.009f);

		// Render entities
		window.render(player);

		for (Entity &platform : platforms)
		{
			window.render(platform);
		}

		for (Entity &platform : platforms)
		{
			if (utils::distanceFrom2Object(player.getPosition(), platform.getPosition()) < 34)
			{
				if (player.getTempPlatform().x != platform.getPosition().x && player.getTempPlatform().y != platform.getPosition().y)
				{
					player.setFallingState(false);
					player.setTempPlatform(platform.getPosition());
					utils::logNumber("x", player.getPosition().x);
					utils::logNumber("y", player.getPosition().y);
				}
			}
			else if (utils::distanceFrom2Object(player.getPosition(), platform.getPosition()) > 34)
			{
				if (utils::distanceFrom2Object(player.getPosition(), player.getTempPlatform()) > 34)
				{
					player.setFallingState(true);
				}
			}
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