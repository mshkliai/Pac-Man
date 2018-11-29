#include "../inc/Game.hpp"

/*********** Structure operator overloading ************/

void	t_cord::operator *= (int x)
{
	this->x *= x;
	this->y *= x;
}

/*********** Constructors ************/

Game::Game(std::string const &fileName)
{
	Parser	parser;
	parser.parseFile(this, fileName);

	this->textureSize = 80;

	speedy.setType("speedy");
	shadow.setType("shadow");

	this->initGameObjects();
	this->gui = new SFMLCore(this->mapSize, this->textureSize);
}

Game::~Game() 
{
	gui->closeWindow();
	delete gui;
}

Game::Game(Game const &obj) 
{ 
	*this = obj; 
}

Game   &Game::operator = (Game const &) 
{
 	return *this;
}

/*********** Game ************/

void	Game::startGame()
{
	this->gui->openWindow();

	if (this->pressSpace("New Game") == esc)
		return;

	this->managePacman();
	this->manageGhosts();
	
	while ( this->handleEvents() != esc )
	{	
		if ( (pacman.getLifes() == 0 && this->gameOver() == esc)
			|| this->checkEndGame() == true )
			return ;

		gui->drawMap(this->map);
		gui->drawEnemyRoom(this->enemyRoom);
		gui->drawScores( pacman.getScores() );

		this->manageJewels();
		this->drawPacman();
		this->drawGhosts();

		this->managePacman();
		this->manageGhosts();

		this->gui->display();
		this->checkCollisions();
	}
}

int 	Game::pressSpace(std::string const &str)
{
	int button;

	while ( (button = this->handleEvents()) != space && button != esc )
	{
		gui->drawMap(this->map);
		gui->drawScores( pacman.getScores() );
		gui->drawSpace(str);
		gui->display();
	}

	return button;
}

int		Game::gameOver()
{
	if (this->pressSpace("Game Over") == esc)
		return esc;
	else
		this->newGame();
	return 0;
}

void	Game::newGame()
{
	this->waitSecond();

	pacman.setPosition(pacmanStartPosition);
	this->initGameObjects();
	this->manageGhosts();
	this->managePacman();

	pacman.setLifes(3);
	pacman.upScore( -pacman.getScores() );
}

/*********** Setters ************/

void	Game::setMap(std::vector<t_cord> newMap) { this->map = newMap; }

void	Game::setEnemyRoom(t_cord newEnemyRoom) { this->enemyRoom = newEnemyRoom; }

void	Game::setPacmanStartPosition(t_cord newCharacterPosition) 
{ 
	this->pacmanStartPosition = newCharacterPosition;
	this->pacman.setPosition(newCharacterPosition); 
}

void	Game::setMapSize(int x, int y)
{
	this->mapSize.x = x;
	this->mapSize.y = y;
}

/*********** Private methods ************/

void	Game::initGameObjects()
{
	speedy.setLife(false);
	this->timer = time(NULL);
	pacman.setMovement(5);
	shadow.setMovement(6);
	pacman.setDirection(up);
	shadow.setPosition(enemyRoom);
	speedy.setPosition(enemyRoom);

	this->initJewels();
}

void	Game::initJewels()
{
	this->jewels.clear();

	for (t_cord jewel : map)
		if (jewel.mayJewel == true)
			jewels.push_back(jewel);
}

/*********** Managers ************/

int 	Game::handleEvents()
{
	switch ( this->gui->getch() )
	{
		case left:	pacman.setDirection(left);		break;
		case right:	pacman.setDirection(right);		break;
		case up:	pacman.setDirection(up);		break;
		case down:	pacman.setDirection(down);		break;
		case space:									return space;	
		case esc:									return esc;
	}

	return 0;
}

void	Game::managePacman()
{
	if (pacman.getMovement() != 5)
		return ;

	pacman.setPaintDirection(0);
	t_cord	newCords = pacman.getPosition();

	if ( this->checkPossibility( pacman.getDirection() ) == true )
	{
		pacman.setPaintDirection( pacman.getDirection() );
		pacman.setOldDirection(0);
	}
	else if ( this->checkPossibility( pacman.getOldDirection() ) == true )
		pacman.setPaintDirection( pacman.getOldDirection() );

	switch ( pacman.getPaintDirection() )
	{
		case left:	newCords.x--;	break;
		case right:	newCords.x++;	break;
		case up:	newCords.y--;	break;
		case down:	newCords.y++;	break;
	}

	this->pacman.setPosition(newCords);
	pacman.setMovement(1);
}

void	Game::manageGhosts()
{
	if (speedy.isAlive() == false && timer + 5 < time(NULL))
	{
		speedy.setLife(true);
		speedy.setNicePosition( *(jewels).begin(), this->map );
	}

	if (shadow.getMovement() != 6)
		return;

	shadow.setNicePosition( pacman.getPosition(), this->map );

	if (speedy.isAlive() == true)
	{
		speedy.setNicePosition( *(jewels.begin()), this->map );

		if (speedy.getPosition().x == -1)
		{
			speedy.setPosition( speedy.getOldPosition() );
			speedy.setNicePosition( pacman.getPosition(), this->map );
		}
	}
	
	shadow.setMovement(1);
}

void	Game::manageJewels()
{
	if (timer + 60 < time(NULL))
	{
		timer = time(NULL);
		this->initJewels();
	}

	gui->drawJewels(this->jewels);
}

void	Game::waitSecond()
{
	int timer = time(NULL);

	while (true)
		if (timer != time(NULL))
			break;
}

/*********** Painting ************/

void	Game::drawPacman()
{
	t_cord position = pacman.getPosition();
	position *= textureSize;

	switch ( pacman.getPaintDirection() )
	{
		case left:	position.x = (position.x + textureSize) - pacman.getMovement() * 20;	break;
		case right:	position.x = (position.x - textureSize) + pacman.getMovement() * 20;	break;
		case up:	position.y = (position.y + textureSize) - pacman.getMovement() * 20;	break;
		case down:	position.y = (position.y - textureSize) + pacman.getMovement() * 20;	break;
		default:	gui->drawPacman( position, pacman.getDirection(), pacman.getLifes() );
	}

	if ( pacman.getPaintDirection() != 0 )
		gui->drawPacman( position, pacman.getPaintDirection(), pacman.getLifes() );

	pacman.setMovement( pacman.getMovement() + 1 );
}

void	Game::drawGhosts()
{
	t_cord position = shadow.getPosition();
	position *= textureSize;

	switch ( shadow.getDirection() )
	{
		case left:	position.x = (position.x + textureSize) - shadow.getMovement() * 16;	break;
		case right:	position.x = (position.x - textureSize) + shadow.getMovement() * 16;	break;
		case up:	position.y = (position.y + textureSize) - shadow.getMovement() * 16;	break;
		case down:	position.y = (position.y - textureSize) + shadow.getMovement() * 16;	break;
	}
	
	gui->drawShadow( position );

	if (speedy.isAlive() == true)
	{
		position = speedy.getPosition();
		position *= textureSize;
		
		switch ( speedy.getDirection() )
		{
			case left:	position.x = (position.x + textureSize) - shadow.getMovement() * 16;	break;
			case right:	position.x = (position.x - textureSize) + shadow.getMovement() * 16;	break;
			case up:	position.y = (position.y + textureSize) - shadow.getMovement() * 16;	break;
			case down:	position.y = (position.y - textureSize) + shadow.getMovement() * 16;	break;
		}
		gui->drawSpeedy(position);
	}

	shadow.setMovement( shadow.getMovement() + 1 );
}

/*********** Collisions ************/

bool	Game::checkPossibility(int direction)
{
	for (t_cord cordMap : map)
	{
		if ( cordMap.isSpace == false )
		{
			switch (direction)
			{
				case left:
					if (pacman.getPosition().x - 1 == cordMap.x && pacman.getPosition().y == cordMap.y)
						return false;
					break;
				case right:
					if (pacman.getPosition().x + 1 == cordMap.x && pacman.getPosition().y == cordMap.y)
						return false;					
					break;
				case down:
					if (pacman.getPosition().y + 1 == cordMap.y && pacman.getPosition().x == cordMap.x)
						return false;					
					break;
				case up:
					if (pacman.getPosition().y - 1 == cordMap.y && pacman.getPosition().x == cordMap.x)
						return false;						
					break;
			}
		}
	}
	return true;
}

bool	Game::checkEndGame()
{
	if ( pacman.getPosition().x < 0 || pacman.getPosition().x >= mapSize.x
		|| pacman.getPosition().y < 0 || pacman.getPosition().y >= mapSize.y )
	{
		if (this->pressSpace("Congratulations!") == esc)
			return true;
		else
			this->newGame();
	}
	return false;
}

void	Game::checkCollisions()
{
	for (auto jewel = this->jewels.begin(); jewel < jewels.end(); jewel++)
	{
		if (pacman.getPosition() == *jewel)
		{
			this->jewels.erase(jewel);
			pacman.upScore(10);
		}
		else if (speedy.getPosition() == *jewel)
			this->jewels.erase(jewel);
	}

	if ( (pacman.getPosition() == speedy.getPosition() && pacman.getDirection() != speedy.getDirection())
	 || pacman.getPosition() == shadow.getPosition() )
	{
		pacman.minorLife(pacmanStartPosition);
		this->managePacman();
		this->waitSecond();
	}
	else if ( pacman.getPosition() == speedy.getPosition() && pacman.getDirection() == speedy.getDirection() )
	{
		speedy.setLife(false);
		speedy.setPosition(enemyRoom);
		pacman.upScore(250);
		timer = time(NULL);	
	}
}