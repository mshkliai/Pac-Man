#ifndef GHOST_H
# define GHOST_H

# include "includes.hpp"
# include "Character.hpp"
# include "Solver.hpp"

class 	Ghost : public Character
{

	public:

		Ghost();
		Ghost(Ghost const &obj);
		~Ghost();

		Ghost &operator = (Ghost const &);

		void	setNicePosition( t_cord const &positionToFind, std::vector<t_cord> const &map );
		void	setType(std::string const &type);
		void	setLife(bool life);

		bool	isAlive();
		t_cord	getOldPosition();


	private:

		t_cord				oldPosition;
		std::vector<t_cord> map;
		std::string			type;
		bool				alive;
		
		void				detectDirection(t_cord const &nicePosition);
		void				prepareMap( t_cord const &positionToFind, std::vector<t_cord> const &map );
};

#endif