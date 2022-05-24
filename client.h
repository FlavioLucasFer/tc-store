#ifndef __TC_STORE_CLIENT__
#define __TC_STORE_CLIENT__

#include <string>
#include <cmath>
#include "db.h"

class client_t
{
	PK(id);
	VARCHAR(name, 255);
	VARCHAR(email, 255);
	VARCHAR(phone_number, 255);
	NUMERIC(debt);
	DELETED_FLAG;

	public:
		client_t () {}
		
		client_t (db::varchar_t name, db::varchar_t email, db::varchar_t phone_number)
		{
			this->set_name(name);
			this->set_email(email);	
			this->set_phone_number(phone_number);
			debt = 0;
		}

	public:
		std::string fdebt ();
		std::string to_string ();
};

#endif

