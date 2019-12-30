#include <iostream>

#include "Parser.h"
#include "Channel.h"

std::vector<Organization> Parser::m_Orgs;

int main(int argc, char* argv[])
{
	// File name argument
	if (argc < 2) {
		std::cout << "Please call with file name." << std::endl;
		return 1;
	}

	// Parse file
	// First command line arg should be file input
	Parser::parse(argv[1]);

	// Leaving as just a print output because im too lazy
	// to write a file.
	for (Organization &org : Parser::m_Orgs) {
		std::cout << "{\"" << org.m_Name << "\":";
		std::cout << org.formatChannels() << "}" << std::endl;
	} 

	return 0;
}
