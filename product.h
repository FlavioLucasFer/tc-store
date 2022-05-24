#ifndef __TC_STORE_PRODUCT__
#define __TC_STORE_PRODUCT__

#include <string>
#include "db.h"

class product_t
{
	PK(id);
	VARCHAR(name, 255);
	VARCHAR(description, 255);
	UINTEGER(amount);
	NUMERIC(price);
	DELETED_FLAG;
	
	public:
		product_t () {}

		product_t(db::varchar_t name, db::varchar_t description, db::uint_t amount, db::numeric_t price)
		{	
			this->set_name(name);
			this->set_description(description);
			this->set_amount(amount);
			this->set_price(price);
		}
		
	public:
		std::string fprice (); 
		std::string to_string ();
};

#endif
