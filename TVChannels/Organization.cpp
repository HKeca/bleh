#include "Organization.h"

Organization::Organization(const std::string& name)
	: m_Name(name) {}

void Organization::insert(Channel channel) {
	m_Channels.push_back(channel);
}

std::string Organization::formatChannels() {
	std::stringstream channels;
	int lineCount = 0;
	int lastLine = m_Channels.size();

	channels << "[";

	for (const Channel& c : m_Channels) {
		channels << "{\"" << c.m_Name << "\":";

		// If last line dont append comma
		if (++lineCount == lastLine)
			channels << "\"" << c.m_Number << "\"}";
		else
			channels << "\"" << c.m_Number << "\"},";
	}

	channels << "]";

	return channels.str();
}