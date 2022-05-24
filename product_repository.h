#ifndef __TC_STORE_PRODUCT_REPOSITORY__
#define __TC_STORE_PRODUCT_REPOSITORY__

#include "base_repository.h"
#include "product.h"

class product_repository_t : public db::base_repository_t<product_t> {};

#endif
