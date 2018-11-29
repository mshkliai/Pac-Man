# include "../inc/SFMLCore.hpp"

/************** Constructors **************/

SFMLCore::SFMLCore(t_cord sizeMap, int textureSize) :
	sizeMap(sizeMap),
	textureSize(textureSize),
	cadrPacman(0),
	cadrShadow(0),
	cadrSpeedy(0)
{
	this->textures.insert ( std::pair<std::string, sf::Texture>("map", sf::Texture()) );
	this->textures.insert ( std::pair<std::string, sf::Texture>("room", sf::Texture()) );
	this->textures.insert ( std::pair<std::string, sf::Texture>("scores", sf::Texture()) );
	this->textures.insert ( std::pair<std::string, sf::Texture>("life", sf::Texture()) );

	this->sprites.insert ( std::pair<std::string, sf::Sprite>("map", sf::Sprite()) );
	this->sprites.insert ( std::pair<std::string, sf::Sprite>("room", sf::Sprite()) );
	this->sprites.insert ( std::pair<std::string, sf::Sprite>("scores", sf::Sprite()) );
	this->sprites.insert ( std::pair<std::string, sf::Sprite>("life", sf::Sprite()) );
	
	this->initSprites(); 
}

SFMLCore::~SFMLCore() {}

SFMLCore::SFMLCore(SFMLCore const &obj) { *this = obj; }

SFMLCore    &SFMLCore::operator = (SFMLCore const &) { return *this; }

/************** Window managers **************/

void 		SFMLCore::openWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(sizeMap.x * textureSize, (sizeMap.y + 2) * textureSize), "Pacman");
}

void 		SFMLCore::closeWindow()
{
    this->window->close();
    delete this->window;
}

void 		SFMLCore::display()
{
	sf::sleep(sf::milliseconds(60));
	this->window->display();
}

int 		SFMLCore::getch()
{
	while ( this->window->pollEvent(this->event) )
	{
		if (event.type == sf::Event::Closed)
			return esc;
		if ( event.type == sf::Event::KeyPressed )
			return event.key.code;
	}

	return 0;
}

/************** Painting **************/

void 		SFMLCore::drawMap(std::vector<t_cord> barriers)
{
	for (auto i = barriers.begin(); i < barriers.end(); i++)
	{
		sprites["map"].setPosition(i->x * textureSize, i->y * textureSize);
		sprites["map"].setColor( i->isSpace == false ? sf::Color(0, 51, 102) : sf::Color::Black );
		
		this->window->draw(sprites["map"]);	
	}
}

void 		SFMLCore::drawPacman(t_cord position, int direction, int lifes)
{
	filePath = "./resources/pacman/" + toStr(cadrPacman++) + "_" + toStr(direction) + ".png";
	cadrPacman > 4 ? cadrPacman >>= 5 : 0;

	sf::Texture pacmanTexture;
	sf::Sprite 	pacmanSprite;

	img.loadFromFile(filePath);
	pacmanTexture.loadFromImage(img);
	pacmanSprite.setTexture(pacmanTexture);
	pacmanSprite.setScale( scale(textureSize, pacmanTexture.getSize().x), scale(textureSize, pacmanTexture.getSize().y) );

	pacmanSprite.setPosition(position.x, position.y);
	this->window->draw(pacmanSprite);

	for (int i = 5; i < lifes + 5; i++)
	{
		sprites["life"].setPosition( (textureSize << 2) * i, textureSize * sizeMap.y ); 
		this->window->draw(sprites["life"]);
	}
}

void 		SFMLCore::drawShadow(t_cord position)
{
	filePath = "./resources/shadow/" + toStr(cadrShadow++) + ".png";
	cadrShadow > 16 ? cadrShadow >>= 5 : 0;

	sf::Texture shadowTexture;
	sf::Sprite 	shadowSprite;

	img.loadFromFile(filePath);
	shadowTexture.loadFromImage(img);
	shadowSprite.setTexture(shadowTexture);
	shadowSprite.setScale( scale(textureSize, shadowTexture.getSize().x), scale(textureSize, shadowTexture.getSize().y) );

	shadowSprite.setPosition(position.x, position.y);
	this->window->draw(shadowSprite);
}

void 		SFMLCore::drawSpeedy(t_cord position)
{
	filePath = "./resources/speedy/" + toStr(cadrSpeedy++) + ".png";
	cadrSpeedy > 7 ? cadrSpeedy >>= 5 : 0;

	sf::Texture speedyTexture;
	sf::Sprite 	speedySprite;

	img.loadFromFile(filePath);
	speedyTexture.loadFromImage(img);
	speedySprite.setTexture(speedyTexture);
	speedySprite.setScale( scale(textureSize, speedyTexture.getSize().x), scale(textureSize, speedyTexture.getSize().y) );

	speedySprite.setPosition(position.x, position.y);
	this->window->draw(speedySprite);	
}

void 		SFMLCore::drawEnemyRoom(t_cord enemyRoom)
{
	sprites["room"].setPosition(enemyRoom.x * textureSize, enemyRoom.y * textureSize);
	this->window->draw(sprites["room"]);
}

void 		SFMLCore::drawJewels(std::vector<t_cord> jewels)
{
	for (t_cord jewel : jewels)
	{
		jewelCircle.setPosition(jewel.x * textureSize + (textureSize >> 1), jewel.y * textureSize + (textureSize >> 1));
		this->window->draw(jewelCircle);
	}
}

void 		SFMLCore::drawScores(int scores)
{
	scoreText.setString("Scores: " + toStr(scores));

	this->window->draw(sprites["scores"]);
	this->window->draw(scoreText);
}

void 		SFMLCore::drawSpace(std::string const &str)
{
	spaceText.setString("                " + str + 
		"\n\n\nPress space for game or esc for exiting");
	
	this->window->draw(spaceText);
}

/************** Private Methods **************/

void 		SFMLCore::initSprites()
{
	font.loadFromFile("./resources/font.ttf");

	if (font.getInfo().family == "")
		throw std::logic_error("Can't get resources, please put binary file in directory, where are the 'resources' directory.");
	
	scoreText.setFont(font);
	scoreText.setPosition(textureSize, sizeMap.y * textureSize - (textureSize >> 2));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(textureSize << 1);

	spaceText.setFont(font);
	spaceText.setPosition( (textureSize * sizeMap.x) >> 2, (textureSize * sizeMap.y) >> 2 );
	spaceText.setFillColor(sf::Color(153, 102, 204));
	spaceText.setCharacterSize( (textureSize << 1) - (textureSize >> 1) );

	textures["map"].create(this->textureSize, this->textureSize);
	sprites["map"].setTexture(textures["map"]);

	textures["room"].loadFromFile("./resources/room.png", sf::Rect<int>(0, 0, 80, 80));
	sprites["room"].setTexture(textures["room"]);

	textures["scores"].create(sizeMap.x * textureSize, sizeMap.y * textureSize);
	sprites["scores"].setTexture(textures["scores"]);
	sprites["scores"].setColor(sf::Color::Black);
	sprites["scores"].setPosition(0, sizeMap.y * textureSize);

	img.loadFromFile("./resources/life.png");
	textures["life"].loadFromImage(img);
	sprites["life"].setTexture(textures["life"]);
	sprites["life"].setScale( scale(textureSize << 1, textures["life"].getSize().x), scale(textureSize << 1, textures["life"].getSize().y) );

	jewelCircle.setRadius( textureSize / 9 );
	jewelCircle.setFillColor(sf::Color(255, 219, 88));
}

std::string SFMLCore::toStr(int num)
{
	std::stringstream 	ss;
	ss << num;

	return ss.str();
}