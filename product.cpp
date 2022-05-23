
#include "product.h"

uint16_t generate_product_id ()
{
	static uint16_t id = 1;
	return id++;
}

std::string product_t::to_string ()
{
	return std::to_string(this->id) + " - " + this->name;
}
