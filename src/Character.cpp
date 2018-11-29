# include "../inc/Character.hpp"

/************** Constructors **************/

Character::Character()
{
	this->position.x = 0;
	this->position.y = 0;

	this->direction = up;
}

Character::Character(Character const &obj) { *this = obj; }

Character::~Character() {}

Character 	&Character::operator = (Character const &) { return *this; }

/************** Getters **************/

t_cord		Character::getPosition() { return this->position; }

int			Character::getDirection() { return this->direction; }

int 		Character::getMovement() { return this->movement; }

/************** Setters **************/

void 		Character::setDirection(int direction) { this->direction = direction; }

void		Character::setPosition(t_cord const &pos) { this->position = pos; }

void		Character::setMovement(int movement) { this->movement = movement; }