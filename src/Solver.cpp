# include "../inc/Solver.hpp"

/************** Overloading operators of structure **************/

bool	t_cord::operator == (struct s_cord const & s)
{
	return (this->x == s.x && this->y == s.y);
}

bool 	t_cord::operator == (int index)
{
	return (this->index == index);
}

/************** Contructors **************/

Solver::Solver() {}

Solver::Solver(Solver const &obj) { *this = obj; }

Solver::~Solver() {}

Solver 	&Solver::operator = (Solver const &) { return *this; }

/************** Setters **************/

void	Solver::setMap(std::vector<t_cord> const &map) { this->map = map; }

void	Solver::setPosition(t_cord const &position) { this->position = position; }

/************** Solver **************/

t_cord  Solver::getPosition()
{
	if (this->waveAlgorithm(1) == -1)
		this->position.x = -1;

	return this->position;
}

/************** Private methods (Algorithm for finding optimal position) **************/

int		Solver::waveAlgorithm(int index)
{
	for (auto i = map.begin(); i < map.end(); i++)
		if (i->index == index)
			makeWaves(i);

	if ( std::find(map.begin(), map.end(), index + 1) == map.end() )
		return -1;

	if ( ( --map.end() )->index == -1 )
		return waveAlgorithm(++index);

	this->findAndSetPosition();
	return 0;
}

void	Solver::makeWaves(iterator i)
{
	for (auto j = map.begin(); j < map.end(); j++)
	{
		i->x++;
		this->checkSimilarity(i, j);

		i->x -= 2;
		this->checkSimilarity(i, j);

		i->x++;
		i->y++;
		this->checkSimilarity(i, j);

		i->y -= 2;
		this->checkSimilarity(i, j);
		i->y++;
	}
}

void	Solver::checkSimilarity(iterator i, iterator j)
{
	if (*j == *i && j->index == -1 && j->isSpace == true)
	{
		j->index = i->index + 1;
		j->parent = &(*i);
	}
}

void	Solver::findAndSetPosition()
{
	auto nicePosition = --map.end();

	while (nicePosition->index != 2)
		*nicePosition = *nicePosition->parent;

	this->position.x = nicePosition->x;
	this->position.y = nicePosition->y;
}