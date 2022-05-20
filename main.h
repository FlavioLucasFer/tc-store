#include <iostream>
#include "lib.h"
#include "client.h"

using choice_t = uint_t;

enum class state_t
{
	main_menu,
	client_menu,
	product_menu,
	sales,
	close,
	panic,
	
#define MAIN_MENU_STATE state_t::main_menu
#define CLIENT_MENU_STATE state_t::client_menu
#define PRODUCT_MENU_STATE state_t::product_menu
#define SALES state_t::sales
#define CLOSE_STATE state_t::close
#define PANIC_STATE state_t::panic
};

enum class client_interface_state_t
{
	menu,
	create,
	list,
	update,
	remove,

#define CLIENT_INTERFACE_MENU_STATE client_interface_state_t::menu
#define CLIENT_INTERFACE_CREATE_STATE client_interface_state_t::create
#define CLIENT_INTERFACE_LIST_STATE client_interface_state_t::list
#define CLIENT_INTERFACE_UPDATE_STATE client_interface_state_t::update
#define CLIENT_INTERFACE_DELETE_STATE client_interface_state_t::remove
};

/*
enum class product_interface_state_t
{
	menu,
	create,
	list,
	update,
	remove,
	sell,
	
#define PRODUCT_INTERFACE_MENU_STATE product_interface_state_t::menu
#define PRODUCT_INTERFACE_CREATE_STATE product_interface_state_t::create
#define PRODUCT_INTERFACE_LIST_STATE product_interface_state_t::list
#define PRODUCT_INTERFACE_UPDATE_STATE product_interface_state_t::update
#define PRODUCT_INTERFACE_REMOVE_STATE product_interface_state_t::remove
#define PRODUCT_INTERFACE_SELL_STATE product_interface_state_t::remove
};
*/

namespace client_interface
{
	client_t* get_client_by_id ();
	void menu ();
	void create ();
	void update ();
	void remove ();
	void list ();
}

/*
namespace product_interface
{
	product_t* get_product_by_id ();
	void menu ();
	void create ();
	void update ();
	void remove ();
	void list ();
	void sell ();
}
*/
