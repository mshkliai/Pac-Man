#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream>
# include <time.h>
# include <vector>
# include <sstream>
# include <fstream>

# include <SFML/Graphics.hpp>

# define esc 36
# define left 71
# define right 72
# define up 73
# define down 74
# define space 57

# define scale(x, y) static_cast<double>(x) / y
# define iterator std::vector<t_cord>::iterator

typedef struct 	s_cord
{
	int 		x, y, index;
	bool		isSpace, mayJewel;
	
	s_cord 		*parent;

	void		operator *= (int x);
	bool		operator == (struct s_cord const & s);
	bool 		operator == (int index);
}				t_cord;

#endif