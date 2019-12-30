#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "Channel.h"

class Organization {
public:
	std::string m_Name;
	std::vector<Channel> m_Channels;

	Organization(const std::string& name);

	void insert(Channel channel);
	std::string formatChannels();
};