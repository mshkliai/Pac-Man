#ifndef SFMLCORE_H
# define SFMLCORE_H

# include "includes.hpp"

class SFMLCore
{
    public:

      SFMLCore();
      SFMLCore(t_cord sizeMap, int textureSize);
      ~SFMLCore();
      SFMLCore(SFMLCore const &obj);

      SFMLCore &operator = (SFMLCore const &);

/************** Window managers **************/

      void	openWindow();
      void	closeWindow();
      void	display();
      int   getch();

/************** Painting **************/


      void	drawMap(std::vector<t_cord> barriers);
      void	drawPacman(t_cord position, int direction, int lifes);
      void	drawShadow(t_cord position);
      void  drawSpeedy(t_cord position);
      void  drawEnemyRoom(t_cord enemyRoom);
      void  drawJewels(std::vector<t_cord> jewels);
      void  drawScores(int scores);
      void  drawSpace(std::string const &str);

    private:

      sf::RenderWindow                    *window;
      sf::Event                           event;

      std::map<std::string, sf::Texture>  textures;
      std::map<std::string, sf::Sprite>   sprites;

      sf::Image                           img;

      sf::Font                            font;
      sf::Text                            scoreText;
      sf::Text                            spaceText;

      sf::CircleShape                     jewelCircle;

  		t_cord 				                      sizeMap;
  		int 				                        textureSize;

  		int 				                        cadrPacman;
      int                                 cadrShadow;
      int                                 cadrSpeedy;

      std::string                         filePath;

  		void				    initSprites();
  		std::string			toStr(int num);
};

#endif