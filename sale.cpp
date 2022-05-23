
#include "sale.h"

uint16_t generate_sale_id ()
{
	static uint16_t id = 1;
	return id++;
}

std::string sale_t::to_string ()
{
	return std::to_string(this->id) + " - " + product.get_name() + ": " + std::to_string(this->quantity) + "x";
}
