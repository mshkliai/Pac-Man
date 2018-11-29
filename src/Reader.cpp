#include "../inc/Reader.hpp"

/************** Constructors **************/

Reader::Reader() {}

Reader::Reader(Reader const &obj) { *this = obj; }

Reader::~Reader() {}

Reader 	&Reader::operator = (Reader const &) { return *this; }

/************** Reader **************/

std::vector<std::string> 	Reader::readMap(std::string const &fileName)
{
	fd.open(fileName);

	if ( fd.is_open() == false )
		throw std::logic_error("Invalid map");

	while ( fd.getline(str, 64) )
		map.push_back( static_cast<std::string>(str) );
	
	fd.close();

	return map;
}