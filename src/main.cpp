# include "../inc/includes.hpp"

# include "../inc/Game.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./pacman maps/map" << std::endl;
		return 0;
	}

	Game 	*game = nullptr;

	try
	{
		game = new Game( static_cast<std::string>(av[1]) );
		game->startGame();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	if (game != nullptr)
		delete game;

	return 0;
}