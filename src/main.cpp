#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <sstream>


#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <Utils.hpp>

void consoleLog()
{
	utils::logTexts("Wellcome to game", "Box Jumping");
	utils::logTime();
};

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

	SDL_Texture *spikeTexture = window.loadTexture("res/gfx/spike.png");

	std::vector<Entity> platforms;
	std::vector<Entity> spikes;

	//100 times per sec
	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	const float gravity = 0.009f;

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

	for (int i = 0; i < 40; i++)
	{
		Entity spike(Vector2f(i * 32, 610), spikeTexture);
		spike.setSize(32, 32);
		spikes.push_back(spike);
	}

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
					case SDLK_UP:
						if (player.getIsStanding())
						{
							player.setIsUp(true);
							player.setIsStanding(false);
						}
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
		consoleLog();
		// Game rendering loop

		// Gravivty Speed
		// capture previous position to perform a simple swept vertical check
		Vector2f prevPos = player.getPosition();
		player.Falling(gravity);

		if (!player.getIsDead())
		{
			system("CLS");
		}

		for (Entity &spike : spikes)
		{
			if (utils::AABBIntersect(player.getPosition(), player.getCurFrame().w, player.getCurFrame().h,
									 spike.getPosition(), spike.getCurFrame().w, spike.getCurFrame().h))
			{
				window.cleanUp();
				player.setDead();
				gameRunning = false;
				utils::logTexts("Game status", "You die!");
			}
		}

		bool onAnyPlatform = false;
		for (Entity &platform : platforms)
		{
			// positions and bounds
			float prevLeft = prevPos.x;
			float prevRight = prevPos.x + player.getCurFrame().w;
			float prevTop = prevPos.y;
			float prevBottom = prevPos.y + player.getCurFrame().h;

			float currLeft = player.getPosition().x;
			float currRight = player.getPosition().x + player.getCurFrame().w;
			float currTop = player.getPosition().y;
			float currBottom = player.getPosition().y + player.getCurFrame().h;

			float platLeft = platform.getPosition().x;
			float platRight = platform.getPosition().x + platform.getCurFrame().w;
			float platTop = platform.getPosition().y;
			float platBottom = platform.getPosition().y + platform.getCurFrame().h;

			bool xOverlapPrev = !(prevRight <= platLeft || prevLeft >= platRight);
			bool xOverlapCurr = !(currRight <= platLeft || currLeft >= platRight);

			bool landedFromAbove = xOverlapCurr && prevBottom <= platTop && currBottom >= platTop;
			bool hitHeadFromBelow = xOverlapCurr && prevTop >= platBottom && currTop <= platBottom;

			const float EPS = 0.001f;

			if (landedFromAbove)
			{
				onAnyPlatform = true;
				if (player.getTempPlatform().x != platform.getPosition().x || player.getTempPlatform().y != platform.getPosition().y)
				{
					player.setFallingState(false);
					player.setIsStanding(true);
					// Snap the player to the top of the platform
					player.setPosition(currLeft, platTop - player.getCurFrame().h);
					player.setTempPlatform(platform.getPosition());
					utils::logNumber("x", player.getPosition().x);
					utils::logNumber("y", player.getPosition().y);
				}
			}
			else if (hitHeadFromBelow)
			{
				// push player down slightly below platform bottom to avoid sticking
				player.setPosition(currLeft, platBottom + EPS);
				player.setIsUp(false);
				// ensure not considered standing
				player.setFallingState(true);
				player.setIsStanding(false);
			}
			else if (utils::AABBIntersect(player.getPosition(), player.getCurFrame().w, player.getCurFrame().h,
										  platform.getPosition(), platform.getCurFrame().w, platform.getCurFrame().h))
			{
				// ambiguous overlap: compute penetration depths (MTV) and resolve on smallest axis
				onAnyPlatform = true;
				float overlapX = std::min(currRight, platRight) - std::max(currLeft, platLeft);
				float overlapY = std::min(currBottom, platBottom) - std::max(currTop, platTop);

				if (overlapX <= 0 || overlapY <= 0)
				{
					continue; // shouldn't happen, but guard
				}

				if (overlapX < overlapY)
				{
					// resolve horizontally
					if (currLeft < platLeft)
						player.setPosition(currLeft - overlapX - EPS, currTop);
					else
						player.setPosition(currLeft + overlapX + EPS, currTop);
				}
				else
				{
					// resolve vertically
					if (currTop < platTop)
					{
						// push up (player was above)
						player.setPosition(currLeft, platTop - player.getCurFrame().h - EPS);
						player.setFallingState(false);
						player.setIsStanding(true);
						player.setTempPlatform(platform.getPosition());
					}
					else
					{
						// push down (player was below)
						player.setPosition(currLeft, platBottom + EPS);
						player.setIsUp(false);
						player.setFallingState(true);
						player.setIsStanding(false);
					}
				}
			}
		}

		if (!onAnyPlatform)
		{
			player.setFallingState(true);
			player.setIsStanding(false);
		}

		// Render everything
		window.render(player);
		for (Entity &platform : platforms)
		{
			window.render(platform);
		}

		for (Entity &spike : spikes)
		{
			window.render(spike);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < (1000 / window.getRefreshRate()))
		{
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	};

	window.cleanUp();
	SDL_Quit();
	system("pause");
	return 0;
};