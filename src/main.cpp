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
			// Main game loop flag
			bool quit = false;

			// Number of frames rendered since the start of the main game loop
			int window_frame = 0;

			SDL_Event e;

			// Load entities
			Entity sky_1 {main.loadTexture("./res/gfx/background_blue_sky.png"), {0, 0, 800, 560}};
			Entity sky_2 {main.loadTexture("./res/gfx/background_blue_sky.png"), {0, 0, 800, 560}};
			Entity grass {main.loadTexture("./res/gfx/ground_grass_1.png"), {0, 0, 32, 32}};
			Character player {main.loadTexture("./res/gfx/hulking_knight.png"), {0, 0, 64, 64}};

			// Initialize the player's destination rect
			main.render(&player, {0, 360, 128, 128});

			// Initialize the skies' destination rect
			main.render(&sky_1, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
			main.render(&sky_2, {800, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

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
						if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_SPACE) player.set_jumping(true);
						if (e.key.keysym.sym == SDLK_DOWN) player.set_crouching(true);
						if (e.key.keysym.sym == SDLK_LEFT) player.set_moving_left(true);
						if (e.key.keysym.sym == SDLK_RIGHT) player.set_moving_right(true);
					}
					else if (e.type == SDL_KEYUP)
					{
						if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_SPACE) player.set_jumping(false);
						if (e.key.keysym.sym == SDLK_DOWN) player.set_crouching(false);
						if (e.key.keysym.sym == SDLK_LEFT) player.set_moving_left(false);
						if (e.key.keysym.sym == SDLK_RIGHT) player.set_moving_right(false);
					}
				}

				// Clear viewport for the next rendering
				SDL_RenderClear(main.getRenderer());

				// Update the window and show the next frame
				player.update();

				// Update the sky position
				if (++window_frame % 30 == 0)
				{
					if (sky_1.getDRect().x < -800)
						sky_1.setDRect({799, 0, 800, 600});
					
					sky_1.setDRect({sky_1.getDRect().x - 1, sky_1.getDRect().y, sky_1.getDRect().w, sky_1.getDRect().h});

					if (sky_2.getDRect().x < -800)
						sky_2.setDRect({799, 0, 800, 600});

					sky_2.setDRect({sky_2.getDRect().x - 1, sky_2.getDRect().y, sky_2.getDRect().w, sky_2.getDRect().h});

					window_frame = 0;
				}

				main.render(&sky_1, sky_1.getDRect());
				main.render(&sky_2, sky_2.getDRect());

				// Render the ground
				for (int i = 0; i < 6; i++)
					main.render(&grass, {(0 + (i * 150)), 450, 150, 150});

				main.render(&player, player.getDRect());

				main.show();
			}

			// Close all subsystems and terminate the program
			SDL_DestroyRenderer(main.getRenderer());
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