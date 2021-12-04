#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Entity.hpp"
#include "Character.hpp"

class Window
{
public:
	Window();

	bool init(const char *p_title, unsigned int p_w, unsigned int p_h);
	SDL_Texture *loadTexture(std::string p_path);
	void render(Entity *p_ent, SDL_Rect p_drect);
	void show();
	void close();

	SDL_Window *getWindow() 	{ return window; }
	SDL_Surface *getSurface() 	{ return surface; }
	SDL_Renderer *getRenderer()	{ return renderer; }

private:
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Renderer *renderer;
};

#endif // WINDOW_H