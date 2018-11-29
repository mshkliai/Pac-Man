#ifndef SOLVER_H
# define SOLVER_H

# include "includes.hpp"

class  Solver
{

	public:
	
		Solver();
		Solver(Solver const &obj);
		~Solver();

		Solver 	&operator = (Solver const &);

		void	setMap(std::vector<t_cord> const &map);
		void	setPosition(t_cord const &position);

		t_cord	getPosition();

	private:
	
		std::vector<t_cord> map;
		t_cord				position;

		int		waveAlgorithm(int index);
		void	makeWaves(iterator i);
		void	checkSimilarity(iterator i, iterator j);
		void	findAndSetPosition();
};

#endif