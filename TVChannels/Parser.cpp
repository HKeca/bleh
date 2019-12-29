#include "Parser.h"

enum class TokenType {
	block, // {
	neutral, // End of line
	name, // left side of :
	value, // Right side of colon
	nop, // no operation
	end // } end of block
};

void Parser::parse(const std::string& fileName)  {
	// open file 
	std::string currentLine;
	std::ifstream listFile(fileName);

	// Current values for parsing
	std::stringstream currentName;
	std::stringstream currentValue;
	bool inBlock = false;
	bool inScope = false;

	// Token types
	TokenType type = TokenType::nop;
	
	// Tmp values for pushing new values
	std::string orgName;
	std::string chName;
	int chNumber = 0;

	if (!listFile.is_open())
		return;
	
	// Main parse loop
	while (std::getline(listFile, currentLine)) {
		for (char token : currentLine) {

			if (type == TokenType::end) {
				if (chName != "" && chNumber != NULL) {
					Parser::findAndPush(orgName, Channel(chName, chNumber));
					type = TokenType::nop;
					continue;
				}
			}

			if (token == ' ') {
				continue;
			}
			else if (token == ']') {
				return;
			}
			else if (token == '{') {
				inScope = true;
				continue;
			}
			else if (token == '\"' && inBlock == false && type != TokenType::value) {
				type = TokenType::name;
				inBlock = true;
				continue;
			}
			else if (token == '\"' && inBlock) {
				type = TokenType::nop;
				inBlock = false;
				continue;
			}
			else if (token == ':') {
				type = TokenType::value;
				continue;
			}
			else if (token == ',' && inScope) {
				type = TokenType::neutral;
			}
			else if (token == '}') {
				type = TokenType::end;
				inScope = false;
				continue;
			}
			else if (token == '\"') {
				inBlock = true;
				continue;
			}
			else if (token == ',' && inScope == false) {
				continue;
			}

			if (type == TokenType::neutral) {

				// Next property
				if (currentName.str() == "orgName") {
					orgName = currentValue.str();
				}
				else if (currentName.str() == "chName") {
					chName = currentValue.str();
				}
				else if (currentName.str() == "chNum") {
					chNumber = std::stoi(currentValue.str());
				}

				// Clear out inputs
				currentName.str(std::string());
				currentValue.str(std::string());

				continue;
			}

			// Add token to stream
			switch (type) {
				case TokenType::name:
					currentName << token;
					break;
				case TokenType::value:
					currentValue << token;
					break;
			}
		}
	}
}

void Parser::findAndPush(const std::string& orgName, Channel channel) {
	for (Organization org : Parser::m_Orgs) {
		if (org.m_Name == orgName) {
			org.insert(channel);
			return;
		}
	}

	std::cout << "New Org" << std::endl;

	Organization newOrg(orgName);
	newOrg.insert(channel);

	Parser::m_Orgs.push_back(newOrg);
}