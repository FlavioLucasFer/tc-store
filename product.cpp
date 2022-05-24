
#include "product.h"

std::string product_t::fprice ()
{
	std::string fprice = std::to_string(this->price);
	return "$"+fprice;
}

std::string product_t::to_string ()
{
	return std::to_string(this->id)+" - "+this->name+" (Price: "+this->fprice()+". amount: "+std::to_string(this->amount)+")";
}
