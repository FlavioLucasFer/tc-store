#include "client.h"

uint16_t generate_client_id ()
{
	static uint16_t id = 1;
	return id++;
}

std::string client_t::to_string ()
{
	return std::to_string(this->id) + " - " + this->name;
}

