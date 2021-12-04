#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class Character : public Entity
{
public:
	Character(SDL_Texture *p_tex, SDL_Rect p_srect);
	Character(SDL_Texture *p_tex, SDL_Rect p_srect, SDL_Rect p_drect);

	// Update the character's position according to the boolean flags
	void update();

	void set_moving_left(bool);
	void set_moving_right(bool);
	void set_crouching(bool);
	void set_jumping(bool);

private:
	// Character movement flags
	bool moving_left;
	bool moving_right;
	bool crouching;
	bool jumping;

	bool moving;

	// Number of frames that passed since the character started moving
	int frame;

	int gravity;
	int jumping_velocity;
};

#endif // CHARACTER_HPP