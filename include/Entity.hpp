#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
	Entity(SDL_Texture *p_tex, SDL_Rect p_srect)
		: texture {p_tex}, srect {p_srect} {}

	Entity(SDL_Texture *p_tex, SDL_Rect p_srect, SDL_Rect p_drect)
		: texture {p_tex}, srect {p_srect}, drect {p_drect} {}

	SDL_Texture *getTexture() { return texture; }
	SDL_Rect &getSRect() { return srect; }
	SDL_Rect &getDRect() { return drect; }

	void setTexture(SDL_Texture *p_tex) { texture = p_tex; }
	void setSRect(SDL_Rect p_srect) { srect = p_srect; }
	void setDRect(SDL_Rect p_drect) { drect = p_drect; }

protected:
	SDL_Texture *texture;
	SDL_Rect srect;
	SDL_Rect drect;
};

#endif // ENTITY_HPP