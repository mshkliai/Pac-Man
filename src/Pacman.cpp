# include "../inc/Pacman.hpp"

/************** Constructors **************/

Pacman::Pacman() : scores(0), lifes(3)
{
	this->oldDirection = up;
	this->paintDirection = up;
}

Pacman::Pacman(Pacman const &obj) { *this = obj; }

Pacman::~Pacman() {}

Pacman	&Pacman::operator = (Pacman const &) { return *this; }

/*************** Getters *****************/

int			Pacman::getOldDirection() { return this->oldDirection; }

int			Pacman::getPaintDirection() { return this->paintDirection; }

int			Pacman::getScores() { return this->scores; }

int			Pacman::getLifes() { return this->lifes; }

/*************** Setters *****************/

void		Pacman::setOldDirection(int direction) { this->oldDirection = direction; }

void		Pacman::setPaintDirection(int direction) { this->paintDirection = direction; }

void		Pacman::setDirection(int direction) 
{ 
	this->oldDirection = this->direction;

	Character::setDirection(direction);
}

void		Pacman::upScore(int scorePrice) { this->scores += scorePrice; }

void		Pacman::setLifes(int lifes) { this->lifes = lifes; }

void		Pacman::minorLife(t_cord const &startPosition) 
{
	this->lifes--;
	this->direction = up;
	this->position = startPosition;
	this->movement = 5;
}