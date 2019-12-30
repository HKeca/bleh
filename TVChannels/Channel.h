#pragma once

#include <string>
#include <vector>

class Channel {
public:
	std::string m_Name;
	int m_Number = 0;
	
	Channel(const std::string& name, int number);
};