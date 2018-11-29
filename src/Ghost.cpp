# include "../inc/Ghost.hpp"

/************** Constructors **************/

Ghost::Ghost() :
	alive(true) {}

Ghost::Ghost(Ghost const &obj) { *this = obj; }

Ghost::~Ghost() {}

Ghost 	&Ghost::operator = (Ghost const &) { return *this; }

/************** Setters **************/

void	Ghost::setNicePosition( t_cord const &positionToFind, std::vector<t_cord> const &map )
{
	Solver 	solver;
	t_cord	nicePosition;

	this->prepareMap(positionToFind, map);

	solver.setMap(this->map);
	solver.setPosition(this->position);
		
	nicePosition = solver.getPosition();

	if (this->type == "shadow" && nicePosition.x == -1)
		throw std::logic_error("Shadow can't find Pac-man");

	this->detectDirection(nicePosition);

	this->oldPosition = this->position;
	this->position = nicePosition;
}

void	Ghost::setType(std::string const &type) { this->type = type; }

void	Ghost::setLife(bool life) { this->alive = life; }

/************** Getters **************/

bool	Ghost::isAlive() { return this->alive; }

t_cord	Ghost::getOldPosition() { return this->oldPosition; }

/************** Private Methods **************/

void	Ghost::detectDirection(t_cord const &nicePosition)
{
	direction = nicePosition.x > this->position.x ? right : direction;
	direction = nicePosition.x < this->position.x ? left  : direction;
	direction = nicePosition.y > this->position.y ? down  : direction;
	direction = nicePosition.y < this->position.y ? up	  : direction;
}

void	Ghost::prepareMap( t_cord const &positionToFind, std::vector<t_cord> const &map )
{
	this->map = map;

	for (auto i = this->map.begin(); i < this->map.end(); i++)
		i->index = -1;

	this->position.index = 1;
	this->position.isSpace = true;
	this->map.push_back(this->position);

	this->map.push_back(positionToFind);
	( --this->map.end() )->index = -1;
	( --this->map.end() )->isSpace = true;
}