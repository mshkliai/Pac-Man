# ifndef PARSER_H
# define PARSER_H

# include "includes.hpp"
# include "Game.hpp"
# include "Reader.hpp"

class 	Game;

class 	Parser
{

	public:
	
		Parser();
		Parser(Parser const &obj);
		~Parser();

		Parser &operator = (Parser const &);

		void	parseFile(Game *game, std::string const &fileName);

	private:

		std::vector<std::string> fileContent;

		Reader					 reader;
		std::vector<t_cord> 	 map;
		t_cord					 characterPosition;
		t_cord					 enemyRoom;
		t_cord					 coordinate;

		void	validate();
	
};


#endif