#ifndef __TC_STORE_CLIENT_REPOSITORY__
#define __TC_STORE_CLIENT_REPOSITORY__

#include "base_repository.h"
#include "client.h"

class client_repository_t : public db::base_repository_t<client_t> {};

#endif
