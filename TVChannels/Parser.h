#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Organization.h"
#include "Channel.h"

class Parser {
public:
	static std::vector<Organization> m_Orgs;

	static void parse(const std::string& fileName);
	static void findAndPush(const std::string& orgName, Channel channel);
};