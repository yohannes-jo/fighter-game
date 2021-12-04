#include "Window.hpp"

Window::Window()
	: window {NULL}, surface {NULL}, renderer {NULL} {}


bool Window::init(const char *p_title, unsigned int p_w, unsigned int p_h)
{
	bool success = true;

	window = SDL_CreateWindow(
		p_title, 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		p_w, 
		p_h, 
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) 
	{
		printf("Window creation failed! SDL Error: %s\n", SDL_GetError());
		success = false;
	} 
	else 
	{
		surface = SDL_GetWindowSurface(window);
		if (surface == NULL) 
		{
			printf("Window surface acquisition failed! SDL Error: %s\n", SDL_GetError());
			success = false;
		} 
		else 
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Window renderer creation failed! SDL Error: %s\n", SDL_GetError());
				success = false;
			}	
		}
	}
	
	return success;
}

SDL_Texture *Window::loadTexture(std::string p_path)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, p_path.c_str());

	return texture;
}

void Window::render(Entity *p_ent, SDL_Rect p_drect)
{
	p_ent->setDRect(p_drect);

	SDL_RenderCopy(renderer, p_ent->getTexture(), &(p_ent->getSRect()), &(p_ent->getDRect()));
}

void Window::show()
{
	SDL_RenderPresent(renderer);
}

void Window::close()
{
	SDL_FreeSurface(surface);
	surface = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
}