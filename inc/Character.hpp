#ifndef CHARACTER_H
# define CHARACTER_H

# include "includes.hpp"

class Character
{

	public:
	
		Character();
		Character(Character const &obj);
		~Character();

		Character &operator = (Character const &);

		t_cord			getPosition();
		int				getDirection();
		int				getMovement();

		virtual void	setDirection(int direction);
		void			setPosition(t_cord const &pos);
		void			setMovement(int movement);

	protected:

		t_cord			position;

		int 			direction;
		int				movement;
	
};


#endif