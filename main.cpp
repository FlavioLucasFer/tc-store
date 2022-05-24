#include "main.h"

bool executing = true;
state_t state = MAIN_MENU_STATE;
client_interface_state_t client_interface_state = CLIENT_INTERFACE_MENU_STATE;
product_interface_state_t product_interface_state = PRODUCT_INTERFACE_MENU_STATE;

product_repository_t product_repository;
client_repository_t client_repository;

choice_t get_menu_choice (uint_t max_value)
{
	choice_t choice;
	
	while (true) {
		lib::lnbr_input<choice_t>("\nChoice: ", choice);
		
		if (choice > 0 && choice <= max_value)
			return choice;
			
		PRINTLN("Invalid option. Please, type a valid option!");
	}
}

void main_menu ()
{
	PRINTLN("WELCOME TO OUR GROCERY STORE! \n");
	PRINTLN("1. Client Management");
	PRINTLN("2. Product Management");
	PRINTLN("3. Sale");
	PRINTLN("4. Close");
	
	choice_t choice = get_menu_choice(4);
	
	switch (choice) {
		case 1:
			state = CLIENT_MENU_STATE;
			break;
		
		case 2:
			state = PRODUCT_MENU_STATE;
			break;
			
		case 3:
			state = SALE;
			break;
			
		case 4:
			state = CLOSE_STATE;
			break;
			
		default:
			state = PANIC_STATE;
			break;
	}	
}

namespace client_interface
{
	void menu ()
	{
		PRINTLN("CLIENT MANAGEMENT\n");
		PRINTLN("1.List all");
		PRINTLN("2.Create");
		PRINTLN("3.Update");
		PRINTLN("4.Delete");
		PRINTLN("5.Return");
	}
	
	bool get_client_by_id (client_t& client) 
	{
		db::pk_t id;
		lib::lnbr_input<db::pk_t>("\nClient ID: ", id);
		if (!client_repository.find_by_id(id, client)) {
			CLEAR_CONSOLE;
			PRINTLN("Client not found!\n");
			return false;
		}

		PRINT('\n');
		PRINTLN(client.get_name());
		PRINTLN(client.get_email());
		PRINTLN(client.get_phone_number());
		PRINT("Debt: ");
		PRINTLN(client.fdebt());

		return true;
	}
	
	void create () 
	{
		std::string name;
		std::string email;
		std::string phone_number;

		lib::lstr_input<std::string>("\nName: ", name);
		lib::lstr_input<std::string>("E-mail: ", email);
		lib::lstr_input<std::string>("Phone number: ", phone_number);

		client_repository.save(client_t(name.c_str(), email.c_str(), phone_number.c_str()));
		CLEAR_CONSOLE;
		PRINTLN("Client successfully created!\n");
	}
	
	void update () 
	{
		client_t client;

		if (!get_client_by_id(client))
			return;

		std::string name;
		std::string email;
		std::string phone_number;

		std::cin.ignore();
		lib::lstr_input<std::string>("\nNew name (TYPE '!k' ENTER TO KEEP CURRENT): ", name);
		lib::lstr_input<std::string>("New e-mail (TYPE '!k' TO KEEP CURRENT): ", email);
		lib::lstr_input<std::string>("New phone number (TYPE '!k' TO KEEP CURRENT): ", phone_number);

		if (name  != "!k")
			client.set_name(name.c_str());
		if (email != "!k")
			client.set_email(email.c_str());
		if (phone_number != "!k")
			client.set_phone_number(phone_number.c_str());

		client_repository.save(client);

		CLEAR_CONSOLE;
		PRINTLN("Client successfully updated!\n");
	}
	
	void remove () 
	{
		client_t client;

		if (!get_client_by_id(client))
			return;

		std::string choice;
		lib::lstr_input<std::string>("\nAre you sure you want to delete this client? Y/n ", choice);
		CLEAR_CONSOLE;

		if (choice != "Y" && choice != "y")
			return;

		client_repository.destroy(client);
		PRINTLN("Client successfully deleted! \n");
	}
	
	void list () 
	{
		CLEAR_CONSOLE;
		PRINTLN("\nClients:\n");

		client_repository.for_each([] (client_t client) {
			PRINTLN(client.to_string());
		});

		PRINT('\n');
	}
	
}

void client_menu ()
{
	client_interface::menu();
	choice_t choice = get_menu_choice(5);
	
	switch (choice) {
		case 1:
			client_interface_state = CLIENT_INTERFACE_LIST_STATE;
			break;
			
		case 2:
			client_interface_state = CLIENT_INTERFACE_CREATE_STATE;
			break;
			
		case 3:
			client_interface_state = CLIENT_INTERFACE_UPDATE_STATE;
			break;
			
		case 4:
			client_interface_state = CLIENT_INTERFACE_DELETE_STATE;
			break;
	
		case 5:
			client_interface_state = CLIENT_INTERFACE_MENU_STATE;
			state = MAIN_MENU_STATE;
			CLEAR_CONSOLE;
			break;
			
		default:
			client_interface_state = CLIENT_INTERFACE_MENU_STATE;
			state = PANIC_STATE;
			CLEAR_CONSOLE;
			break;
	}
}

void client_i ()
{
	do {
		switch (client_interface_state) {
			case CLIENT_INTERFACE_MENU_STATE:
				client_menu();
				break;
				
			case CLIENT_INTERFACE_CREATE_STATE:
				client_interface::create();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_LIST_STATE:
				client_interface::list();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_UPDATE_STATE:
				client_interface::update();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_DELETE_STATE:
				client_interface::remove();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			default: //return
				CLEAR_CONSOLE;
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				state = MAIN_MENU_STATE;
				break;
				
		}
	} while (state == CLIENT_MENU_STATE);
}

namespace product_interface
{
	void menu ()
	{
		PRINTLN("PRODUCT MANAGEMENT\n");
		PRINTLN("1. List all");
		PRINTLN("2. Create");
		PRINTLN("3. Update");
		PRINTLN("4. Delete");
		PRINTLN("5. Return");
	}
	
	bool get_product_by_id (product_t& product) 
	{
		db::pk_t id;
		lib::lnbr_input<db::pk_t>("\nProduct ID: ", id);
		if (!product_repository.find_by_id(id, product)) {
			CLEAR_CONSOLE;
			PRINTLN("Product not found!\n");
			return false;
		}

		PRINT('\n');
		PRINTLN(product.get_name());
		PRINTLN(product.get_description());
		PRINT("Amount: ");
		PRINTLN(product.get_amount());
		PRINT("Price: ");
		PRINTLN(product.fprice());

		return true;
	}
	
	void create () 
	{
		std::string name;
		std::string description;
		product_t::price_t price;
		product_t::amount_t amount;

		lib::lstr_input<std::string>("\nName: ", name);
		lib::lstr_input<std::string>("Description: ", description);
		lib::lnbr_input<product_t::price_t>("Price: $", price);
		lib::lnbr_input<product_t::amount_t>("Amount: ", amount);

		product_repository.save(product_t(
			name.c_str(), 
			description.c_str(), 
			amount,
			price
		));
		CLEAR_CONSOLE;
		PRINTLN("Product successfully created!\n");
	}
	
	void update () 
	{
		product_t product;

		if (!get_product_by_id(product))
			return;

		std::string name;
		std::string description;
		std::string price;
		std::string amount;

		std::cin.ignore();
		lib::lstr_input<std::string>("\nNew name (TYPE '!k' ENTER TO KEEP CURRENT): ", name);
		lib::lstr_input<std::string>("New description (TYPE '!k' TO KEEP CURRENT): ", description);
		lib::lnbr_input<std::string>("New price (TYPE '!k' ENTER TO KEEP CURRENT): $", price);
		lib::lnbr_input<std::string>("New amount (TYPE '!k' ENTER TO KEEP CURRENT): ", amount);

		if (name  != "!k")
			product.set_name(name.c_str());
		if (description != "!k")
			product.set_description(description.c_str());
		if (price != "!k")
			product.set_price(std::stod(price));
		if (amount != "!k")
			product.set_amount(std::strtoull(amount.c_str(), nullptr, 0));

		product_repository.save(product);

		CLEAR_CONSOLE;
		PRINTLN("Product successfully updated!\n");
	}
	
	void remove () 
	{
		product_t product;

		if (!get_product_by_id(product))
			return;

		std::string choice;
		lib::lstr_input<std::string>("\nAre you sure you want to delete this product? Y/n ", choice);
		CLEAR_CONSOLE;

		if (choice != "Y" && choice != "y")
			return;

		product_repository.destroy(product);
		PRINTLN("Product successfully deleted! \n");
	}
	
	void list () 
	{
		CLEAR_CONSOLE;
		PRINTLN("\nProducts:\n");

		product_repository.for_each([] (product_t product) {
			PRINTLN(product.to_string());
		});

		PRINT('\n');
	}
	
}

void product_menu ()
{
	product_interface::menu();
	choice_t choice = get_menu_choice(5);
	
	switch (choice) {
		case 1:
			product_interface_state = PRODUCT_INTERFACE_LIST_STATE;
			break;
			
		case 2:
			product_interface_state = PRODUCT_INTERFACE_CREATE_STATE;
			break;
			
		case 3:
			product_interface_state = PRODUCT_INTERFACE_UPDATE_STATE;
			break;
			
		case 4:
			product_interface_state = PRODUCT_INTERFACE_DELETE_STATE;
			break;
	
		case 5:
			product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
			state = MAIN_MENU_STATE;
			CLEAR_CONSOLE;
			break;
			
		default:
			product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
			state = PANIC_STATE;
			CLEAR_CONSOLE;
			break;
	}
}

void product_i ()
{
	do {
		switch (product_interface_state) {
			case PRODUCT_INTERFACE_MENU_STATE:
				product_menu();
				break;
				
			case PRODUCT_INTERFACE_CREATE_STATE:
				product_interface::create();
				product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
				break;
				
			case PRODUCT_INTERFACE_LIST_STATE:
				product_interface::list();
				product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
				break;
				
			case PRODUCT_INTERFACE_UPDATE_STATE:
				product_interface::update();
				product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
				break;
				
			case PRODUCT_INTERFACE_DELETE_STATE:
				product_interface::remove();
				product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
				break;
				
			default: //return
				CLEAR_CONSOLE;
				product_interface_state = PRODUCT_INTERFACE_MENU_STATE;
				state = MAIN_MENU_STATE;
				break;
				
		}
	} while (state == PRODUCT_MENU_STATE);
}

void sale ()
{
	client_t client;
	product_t product;
	PRINTLN("SALE");

	if (!product_interface::get_product_by_id(product))
		return;
	if (!client_interface::get_client_by_id(client))
		return;

	product_t::amount_t amount;
	lib::lnbr_input<product_t::amount_t>("\nAmount: ", amount);
	product_t::price_t total_price = amount * product.get_price();

	PRINTLN("SALE REVIEW\n");
	PRINT("Client: ");
	PRINTLN(client.get_name());
	PRINT("Product: ");
	PRINTLN(product.get_name());
	PRINT("Amount: ");
	PRINTLN(amount);
	PRINT("Total price: $");
	PRINTLN(total_price);

	std::string choice;
	lib::lstr_input<std::string>("\nConfirm sale? Y/n ", choice);
	CLEAR_CONSOLE;

	if (choice != "Y" && choice != "y")
		return;
	
	product.set_amount(product.get_amount()-amount);
	product_repository.save(product);

	client.set_debt(client.get_debt()+total_price);
	client_repository.save(client);

	PRINTLN("Product successfully sold! \n");
}

int main ()
{
	do {
		switch (state) {
			case MAIN_MENU_STATE:
				main_menu();
				break;
				
			case CLIENT_MENU_STATE:
				CLEAR_CONSOLE;
				client_i();
				break;
				
			case PRODUCT_MENU_STATE:
				CLEAR_CONSOLE;
				product_i();
				break;
				
			case SALE:
				CLEAR_CONSOLE;
				sale();
				state = MAIN_MENU_STATE;
				break;
				
			case CLOSE_STATE:
				CLEAR_CONSOLE;
				executing = false;
				break;
				
			default:
				CLEAR_CONSOLE;
				PRINT("PANIC: An unexpected error has occurred!");
				executing = false;
				break;		
		}
	} while (executing);
	return 0;
}



















