#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

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
	// Entity platform0(150,140,grassTexture);
	
	std::vector<Entity> entities;
	std::vector<Entity> platforms;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	int range = 300 - 100 + 1;
	Entity player(Vector2f((rand() % range + 100), 100 ), playerTexture);
	for (int i = 0; i < 20; i++)
	{
		int num = rand() % range + 100;
		Entity platform(Vector2f(i * 64, 600 - num), platformTexture);
		platform.setSize(64, 32);
		platforms.push_back(platform);
	}

	// for (int i = 0; i < 2; ++i)
	// {
	// 	Entity platform(Vector2f((250 + 1) * i ,605), grassTexture);
	// 	entities.push_back(platform);
	// }

	Entity platform1(Vector2f(250, 0), grassTexture);
	// Entity platform2(Vector2f(250 + 32 * 4,605), grassTexture);

	entities.push_back(platform1);
	// entities.push_back(platform2);

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
			}
			accumulator -= timeStep;
		}

		/* code */
		// const float alpha = accumulator / timeStep;

		window.clear();
		// window.render(platform0);
		// entities[0].setPosition(entities[0].getPosition().x,entities[0].getPosition().y + 0.5f);
		player.Falling(0.005f);

		// Render entities
		window.render(player);

		for (Entity &platform : platforms)
		{
			window.render(platform);
		}

		// std::cout << utils::hireTimeInSeconds() << std::endl;

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
}