#include "Organization.h"

Organization::Organization(const std::string& name)
	: m_Name(name) {}

void Organization::insert(Channel channel) {
	m_Channels.push_back(channel);
}