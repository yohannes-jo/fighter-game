#include "Character.hpp"

Character::Character(SDL_Texture *p_tex, SDL_Rect p_srect)
	: Entity(p_tex, p_srect)
{
	moving_left = false;
	moving_right = false;
	crouching = false;
	jumping = false;

	moving = false;

	frame = 0;
	jumping_velocity = 50;
	gravity = 5;	
}

void Character::update()
{
	if (moving_left)
	{
		moving = true;
		if (++frame % 60 == 0)
		{
			if (srect.x < 256)
			{
				srect.x += 64;
			}
			else
			{
				srect.x = 64;
			}
			frame = 0;
		}

		if (drect.x >= 0 && frame % 3 == 0) drect.x -= 1;
	}
	else if (moving_right)
	{
		moving = true;
		if (++frame % 60 == 0)
		{
			if (srect.x < 256)
			{
				srect.x += 64;
			}
			else
			{
				srect.x = 64;
			}
			frame = 0;
		}

		if (drect.x <= 672 && frame % 3 == 0) drect.x += 1;
	}
	
	if (jumping || drect.y < 360)
	{
		moving = true;
		if (++frame % 15 == 0 && drect.y <= 360 + jumping_velocity)
		{
			drect.y -= jumping_velocity;

			if (jumping_velocity >= -50)
			{
				jumping_velocity -= gravity;
			}
			else
			{
				jumping_velocity = 50;
			}
			frame = 0;
		}
	}

	if (!(moving_left || moving_right || jumping || drect.y < 360))
	{
		moving = false;
	}

	// reset the velocity everytime the sprite touches the ground
	if (drect.y == 360)
	{
		jumping_velocity = 50;
	}

	// reset sprite when it stops moving
	if (!moving)
	{
		srect.x = 0;
		srect.y = 0;
		srect.w = 64;
		srect.h = 64;

		frame = 0;
		jumping_velocity = 50;
		drect.y = 360;
	}
}

void Character::set_moving_left(bool p_flag) { moving_left = p_flag; }
void Character::set_moving_right(bool p_flag) { moving_right = p_flag; }
void Character::set_jumping(bool p_flag) { jumping = p_flag; }
void Character::set_crouching(bool p_flag) { crouching = p_flag; }