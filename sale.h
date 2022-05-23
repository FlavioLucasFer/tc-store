#ifndef __TC_STORE_SALE__
#define __TC_STORE_SALE__

#include "lib.h"
#include "product.h"
#include "client.h"

uint16_t generate_sale_id ();

class sale_t
{
	OO_ENCAPSULATE_RO(uint16_t, id);
	OO_ENCAPSULATE(client_t, client);
	OO_ENCAPSULATE(product_t, product);
	OO_ENCAPSULATE(uint_t, quantity);
	OO_ENCAPSULATE(double, price);
	
	public:
		sale_t () {}
		
		sale_t (client_t client, product_t product, uint_t quantity, double price)
		{	
			this->id = generate_sale_id();
			this->client = client;
			this->product = product;
			this->quantity = quantity;
			this->price = price;
		}
	
		std::string to_string();
};

#endif
