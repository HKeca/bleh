#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Organization.h"
#include "Channel.h"

class Parser {
public:
	// Keep a vector of organizations, when naming you want to chose something more specific and less generic
	// In your file you called it "list", when reading this it tells me nothing... whats it a list of
	static std::vector<Organization> m_Orgs;

	static void parse(const std::string& fileName);
	static void findAndPush(const std::string& orgName, Channel& channel);
};