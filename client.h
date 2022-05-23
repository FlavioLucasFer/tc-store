#ifndef __TC_STORE_CLIENT__
#define __TC_STORE_CLIENT__

#include <cstring>

#include "lib.h"

uint16_t generate_client_id ();

class client_t
{
	private:
		char name[255];
		char email[255];
		char phone_number[255];
		double total_spent;
	
	OO_ENCAPSULATE_RO(uint16_t, id);

	public:
		client_t () {}
		
		client_t (const char* name, const char* email, const char* phone_number)
		{
			this->id = generate_client_id();	
			strcpy(this->name, name);
			strcpy(this->email, email);
			strcpy(this->phone_number, phone_number);
			this->total_spent = 0;
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
		
		inline char* get_email ()
		{
			return this->email;
		}
		
		inline void set_email (const char* email)
		{
			strcpy(this->email, email);
		}
		
		inline char* get_phone_number ()
		{
			return this->phone_number;
		}
		
		inline void set_phone_number (const char* phone_number)
		{
			strcpy(this->phone_number, phone_number);
		}
		
		inline double get_total_spent ()
		{
			return this->total_spent;
		}
		
		inline void set_total_spent (double value)
		{
			this->total_spent += value;
		}
			
		std::string to_string ();
};

#endif

