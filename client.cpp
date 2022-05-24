#include "client.h"

std::string client_t::fdebt ()
{
	std::string sdebt = std::to_string(this->debt);
	return "$"+sdebt;
}

std::string client_t::to_string ()
{
	return std::to_string(this->id)+" - "+this->name+" (Debt: "+this->fdebt()+")";
}


