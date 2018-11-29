# include "../inc/Parser.hpp"

/************** Constructors **************/

Parser::Parser() 
{
	characterPosition.x = -1;
	enemyRoom.x = -1;
}

Parser::Parser(Parser const &obj) { *this = obj; }

Parser::~Parser() {}

Parser 	&Parser::operator = (Parser const &) { return *this; }

/************** Parser **************/

void	Parser::parseFile(Game *game, std::string const &fileName)
{
	this->fileContent = reader.readMap(fileName);

	for (size_t i = 0; i < this->fileContent.size(); i++)
	{
		for (size_t j = 0; j < this->fileContent[i].length(); j++)
		{
			coordinate.x = j;
			coordinate.y = i;
			
			switch (this->fileContent[i][j])
			{
				case '#':	coordinate.isSpace = false;
							coordinate.mayJewel = false;
							map.push_back(coordinate);			break;

				case ' ':	coordinate.isSpace = true;
							coordinate.mayJewel = true;
							map.push_back(coordinate);			break;

				case 'P':	if (characterPosition.x != -1)
								throw std::logic_error("Only one pacman on map!");
							characterPosition = coordinate;
							characterPosition.isSpace = true;	break;

				case 'G':	if (enemyRoom.x != -1)
								throw std::logic_error("Only one ghost-room on map!");
							enemyRoom = coordinate;
							coordinate.mayJewel = false;
							coordinate.isSpace = true;
					 		map.push_back(coordinate);			break;
				
				default:	throw std::logic_error("Only '#', ' ', 'P', 'G' symbols in map declaration");
			}
		}
	}

	this->validate();

	map.push_back(characterPosition);

	game->setMap(map);
	game->setPacmanStartPosition(characterPosition);
	game->setEnemyRoom(enemyRoom);
	game->setMapSize( this->fileContent.begin()->length(), this->fileContent.size() );
}

/************** Validator **************/

void	Parser::validate()
{
	if (characterPosition.x == -1)
		throw std::logic_error("No pacman! ('P')");
	else if (enemyRoom.x == -1)
		throw std::logic_error("No ghosts room! ('G')");
	else if (this->fileContent.size() > 30 || this->fileContent.size() < 15)
		throw std::logic_error("Bad size of map! (Min. 15, Max. 30)");

	size_t mapSize = this->fileContent.begin()->length();
	
	for (std::string str : this->fileContent)
		if ( str.length() != mapSize )
			throw std::logic_error("The map must be rectangular!");
}