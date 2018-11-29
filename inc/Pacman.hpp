# ifndef PACMAN_H
# define PACMAN_H

# include "includes.hpp"
# include "Character.hpp"
# include "SFMLCore.hpp"

class  	Pacman : public Character
{

	public:
		
		Pacman();
		Pacman(Pacman const &obj);
		~Pacman();

		Pacman &operator = (Pacman const &);

		int		getOldDirection();
		int		getPaintDirection();
		int		getScores();
		int		getLifes();

		void	setOldDirection(int direction);
		void	setPaintDirection(int direction);
		void	setDirection(int direction);
		void	upScore(int scorePrice);
		void	setLifes(int lifes);
		void	minorLife(t_cord const &startPosition);

	private:

		int 	oldDirection;
		int		paintDirection;
		int		scores;
		int		lifes;
	
};

#endif