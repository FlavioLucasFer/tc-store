#include "main.h"

bool executing = true;
state_t state = MAIN_MENU_STATE;
client_interface_state_t client_interface_state = CLIENT_INTERFACE_MENU_STATE;

choice_t get_menu_choice (uint_t max_value)
{
	choice_t choice;
	
	while (true) {
		lib::lnbr_input<choice_t>("\n Choice: ", choice);
		
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
	PRINTLN("3. Sales");
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
			state = SALES;
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
		PRINTLN("1. List all");
		PRINTLN("2. Create");
		PRINTLN("3. Update");
		PRINTLN("4. Delete");
		PRINTLN("5. Return");
	}
	
	//client_t* get_client_by_id () {}
	
	//void create () {}
	
	//void update () {}
	
	//void remove () {}
	
	//void list () {}
	
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
				//client_interface::create();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_LIST_STATE:
				//client_interface::list();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_UPDATE_STATE:
				//client_interface::update();
				client_interface_state = CLIENT_INTERFACE_MENU_STATE;
				break;
				
			case CLIENT_INTERFACE_DELETE_STATE:
				//client_interface::remove();
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

int main ()
{
	do {
		switch (state) {
			case MAIN_MENU_STATE:
				main_menu();
				break;
				
			case CLIENT_MENU_STATE:
				CLEAR_CONSOLE;
				PRINTLN("menu cliente");
				break;
				
			case PRODUCT_MENU_STATE:
				CLEAR_CONSOLE;
				PRINTLN("menu produto");
				break;
				
			case SALES:
				CLEAR_CONSOLE;
				PRINTLN("vendas");
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



















