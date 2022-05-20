#ifndef __TC_STORE_CLIENT__
#define __TC_STORE_CLIENT__

#include "lib.h"

uint16_t generate_client_id ();

class client_t
{
	OO_ENCAPSULATE_RO(uint16_t, id);
	OO_ENCAPSULATE(std::string, name);
	OO_ENCAPSULATE(std::string, email);
	OO_ENCAPSULATE(std::string, phone_number);

	public:
		client_t () {}
		
		client_t (std::string name, std::string email, std::string phone_number)
		{
			this->id = generate_client_id();	
			this->name = name;
			this->email = email;
			this->phone_number = phone_number;
		}
		
		std::string to_string ();
};

#endif

