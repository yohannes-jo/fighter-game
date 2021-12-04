#include <stdio.h>
#include <SDL2/SDL.h>

#include "Window.hpp"
#include "Entity.hpp"
#include "Character.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Initialize SDL
bool init();

int main(int argc, char const *argv[])
{

	if (!init()) 
	{
		printf("SDL could not be initialized!");
		return 1;
	} 
	else 
	{
		Window main;

		if (!main.init("DIBAQ V-1.0", SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			printf("Main window could not be initialized!");
			return 1;
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			// Load entities
			Entity sky {main.loadTexture("./res/gfx/background_blue_sky.png"), {0, 0, 800, 560}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}};
			Entity grass {main.loadTexture("./res/gfx/ground_grass_1.png"), {0, 0, 32, 32}};
			Character player {main.loadTexture("./res/gfx/hulking_knight.png"), {0, 0, 64, 64}};

			// Render the player at the starting position
			main.render(&player, {0, 360, 128, 128});

			// Main game loop
			while (!quit)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_UP) player.set_jumping(true);
						if (e.key.keysym.sym == SDLK_DOWN) player.set_crouching(true);
						if (e.key.keysym.sym == SDLK_LEFT) player.set_moving_left(true);
						if (e.key.keysym.sym == SDLK_RIGHT) player.set_moving_right(true);
					}

					else if (e.type == SDL_KEYUP)
					{
						if (e.key.keysym.sym == SDLK_UP) player.set_jumping(false);
						if (e.key.keysym.sym == SDLK_DOWN) player.set_crouching(false);
						if (e.key.keysym.sym == SDLK_LEFT) player.set_moving_left(false);
						if (e.key.keysym.sym == SDLK_RIGHT) player.set_moving_right(false);
					}

				}

				// Update the window and show the next frame
				player.update();

				// Render the sky
				main.render(&sky, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

				// Render the ground
				for (int i = 0; i < 6; i++)
					main.render(&grass, {(0 + (i * 150)), 450, 150, 150});

				main.render(&player, player.getDRect());

				main.show();
			}

			// Close all subsystems and terminate the program
			main.close();
			SDL_Quit();
		}
	}

	return 0;
}

bool init()
{
	bool success = true;

	// SDL initializer returns 0 when there are no errors
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Init failed! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}