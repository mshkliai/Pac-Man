# ifndef READER_H
# define READER_H

# include "includes.hpp"

class Reader
{
	public:
	
		Reader();
		Reader(Reader const &obj);
		~Reader();

		Reader &operator = (Reader const &);

		std::vector<std::string> readMap(std::string const &fileName);

	private:

		std::string 				mapName;
		std::ifstream				fd;
		char						str[64];
		std::vector<std::string>	map;
	
};

#endif