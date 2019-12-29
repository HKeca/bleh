#include <iostream>

#include "Parser.h"

std::vector<Organization> Parser::m_Orgs;

int main(int argc, char* argv[])
{
	/*if (argc < 2) {
		std::cout << "Please call with file name." << std::endl;
		return 1;
	}*/

	Parser::parse("input.txt");

	for (Organization org : Parser::m_Orgs) {
		std::cout << org.m_Name << std::endl;
		std::cout << org.m_Channels.size() << std::endl;
		for (Channel c : org.m_Channels) {
			std::cout << c.m_Name << ": " << c.m_Number << std::endl;
		}
	} 

	return 0;
}
