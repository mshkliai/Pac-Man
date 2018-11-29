#ifndef GAME_H
# define GAME_H

# include "includes.hpp"

# include "SFMLCore.hpp"
# include "Pacman.hpp"
# include "Ghost.hpp"
# include "Parser.hpp"

class Game
{
    public:

        Game();
        Game(std::string const &fileName);
        ~Game();
        Game(Game const &obj);

        Game &operator = (Game const &);

        /*********** Game ************/

        void	startGame();
        int     pressSpace(std::string const &str);
        int     gameOver();
        void    newGame();

        /*********** Setters ************/

        void	setMap(std::vector<t_cord> newMap);
        void	setEnemyRoom(t_cord newEnemyRoom);
        void	setPacmanStartPosition(t_cord newCharacterPosition);
        void	setMapSize(int x, int y);

    private:

    	SFMLCore					*gui;

        /*********** Characters ************/

    	Pacman						pacman;
    	Ghost						shadow;
        Ghost                       speedy;

        /*********** Game process variables ************/
    	
        int 						textureSize;
        int                         timer;

    	t_cord 						mapSize;
    	t_cord						enemyRoom;
        t_cord                      pacmanStartPosition;

    	std::vector<t_cord> 		map;
        std::vector<t_cord>         jewels;

        /*********** Private methods ************/

    	void	initGameObjects();
        void    initJewels();

        /*********** Managers ************/
    	
        int 	handleEvents();
    	void	managePacman();
    	void	manageGhosts();
        void    manageJewels();
        void    waitSecond();

        /*********** Painting ************/
    	
    	void	drawPacman();
        void    drawGhosts();

        /*********** Collisions ************/

    	bool	checkPossibility(int direction);
        bool    checkEndGame();
        void    checkCollisions();
};

#endif