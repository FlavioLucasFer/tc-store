#ifndef __TC_STORE_PRODUCT__
#define __TC_STORE_PRODUCT__

#include <cstring>
#include <string>

#include "lib.h"

uint16_t generate_product_id ();

class product_t
{
	private:
		char name[255];
		char description[255];
	
	OO_ENCAPSULATE_RO(uint16_t, id);
	OO_ENCAPSULATE(double, price);
	
	public:
		product_t () {}
		
		product_t (const char* name, const char* description, double price)
		{	
			this->id = generate_product_id();
			strcpy(this->name, name);
			strcpy(this->description, description);
			this->price = price;
		}
		
	public:
		inline char* get_name () 
		{
			return this->name;
		}
		
		inline void set_name (const char* name)
		{
			strcpy(this->name, name);
		}
		
		inline char* get_description ()
		{
			return this->description;
		}
		
		inline void set_description (const char* description)
		{
			strcpy(this->description, description);
		}
		
		std::string to_string ();
};

#endif
