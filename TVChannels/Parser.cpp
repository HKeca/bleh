#include "Parser.h"

enum class TokenType {
	block,		// Start of block
	eol,		// End of line
	name,		// Key
	value,		// Value
	end,		// end of block
	nop			// no operation
};

// A few things that can be improved in your Read() func
// Variable naming specifically. Avoid single letter vars unless a for(i) loop obviously;
// When looking over someones code where you dont have context a variable named
// m_Orgs would make more sense than just 'l'.
// The last thing is if you take the filename as param it makes your code more portable
void Parser::parse(const std::string& fileName)  {
	// open file 
	std::string currentLine;
	std::ifstream listFile(fileName);

	// Current values for parsing
	std::stringstream currentName;
	std::stringstream currentValue;

	// These are a bit arbitrary to my code style of nameing
	// inBlock means we are current reading a value within quotes
	// inScope means we are in a block of values (inbetween the {})
	bool inBlock = false;
	bool inScope = false;

	// Token types
	// We need to track the token type to decide what to do 
	// with the next input
	TokenType type = TokenType::nop;
	
	// These values are used to keep the values for the channel input
	// when we flush the string streams
	std::string orgName;
	std::string channelName;
	int channelNumber = 0;
	
	// Just checking to make sure the file actually opened
	if (!listFile.is_open())
		return;
	
	// Main parse loop
	while (std::getline(listFile, currentLine)) {
		for (char token : currentLine) {

			// If the token type is the end of a scope
			// we want to push a the new channel to the organization
			if (type == TokenType::end) {
				Parser::findAndPush(orgName, Channel(channelName, channelNumber));
				type = TokenType::nop;
				continue;
			}
			
			// Then we check for command tokens.
			// (quotes, brackets, and setting which value we are currently adding to)
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
			// If we are not in a block means this is the first quote, so we to start tracking the value
			// This one specifically checks for name, so we dont want value hence the != TokenType::value
			// After this token we are in a block so we set it to true
			else if (token == '\"' && inBlock == false && type != TokenType::value) {
				type = TokenType::name;
				inBlock = true;
				continue;
			}
			// If we are in a block and we come across another quote
			// we must have hit the end of a block
			// set the next action to nop (do nothing) and leave the block
			else if (token == '\"' && inBlock) {
				type = TokenType::nop;
				inBlock = false;
				continue;
			}
			// The colon tells use we are taking a value now
			else if (token == ':') {
				type = TokenType::value;
				continue;
			}
			// The comma signals end of the line.
			// So take the input from the string stream and clear it
			else if (token == ',' && inScope) {
				type = TokenType::eol;
			}
			// End of scope
			// We take the temp values from the streams and
			// make a new channel with them
			else if (token == '}') {
				type = TokenType::end;
				inScope = false;
				continue;
			}
			// If we hit a quote we are in a block now
			else if (token == '\"') {
				inBlock = true;
				continue;
			}
			// This line avoids commas that are outside of brackets
			else if (token == ',' && inScope == false) {
				continue;
			}

			// End of line
			// take the value from the streams and flush them
			if (type == TokenType::eol) {

				// Next property
				if (currentName.str() == "orgName") {
					orgName = currentValue.str();
				}
				else if (currentName.str() == "chName") {
					channelName = currentValue.str();
				}
				else if (currentName.str() == "chNum") {
					channelNumber = std::stoi(currentValue.str());
				}

				// Clear out streams
				currentName.str(std::string());
				currentValue.str(std::string());

				continue;
			}

			// if token doesnt match any command it must be a
			// value. Add it to the proper string
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
	
	listFile.close();
}

// This adds a channel to a org if it exists
// or creates a new org and adds the channel
// I think this would be the function "createList" in your code
void Parser::findAndPush(const std::string& orgName, Channel& channel) {
	// Find existing org and insert
	for (Organization &org : m_Orgs) {
		if (org.m_Name == orgName) {
			org.insert(channel);
			return;
		}
	}

	// Or make a new org
	Organization newOrg(orgName);
	newOrg.insert(channel);

	m_Orgs.push_back(newOrg);
}
