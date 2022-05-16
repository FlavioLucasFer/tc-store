#ifndef __LIB__
#define __LIB__

#include <list>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <inttypes.h>

using uint_t = unsigned int;

#define PRINT(STR) std::cout << STR
#define PRINTLN(STR) std::cout << STR << std::endl

#define DEBUG 1

#if DEBUG
	#define CLEAR_CONSOLE
	#define DPRINT(STR) PRINT(STR)
	#define DPRINTLN(STR) PRINTLN(STR)
#else
	#define CLEAR_CONSOLE system("clear")
	#define DPRINT(STR)
	#define DPRINTLN(STR)
#endif

#define OO_ENCAPSULATE(TYPE, VAR) \
	private: \
		TYPE VAR; \
	\
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		} \
		\
		inline void set_##VAR (TYPE VAR) \
		{ \
			this->VAR = VAR; \
		} 
		
#define OO_ENCAPSULATE_RO(TYPE, VAR) \
	private: \
		TYPE VAR; \
	\
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		}

namespace lib 
{
	// string input
	template <typename T>
	void str_input (T& var)
	{
		std::getline(std::cin, var);
		std::cin.ignore();
	}

	// labeled string input
	template <typename T>
	void lstr_input (const char msg[], T& var)
	{
		PRINT(msg);
		str_input(var);
	}

	// numeric (int, long, double...) input
	template <typename T>
	void nbr_input (T& var)
	{
		std::cin >> var;
		std::cin.ignore();
	}

	// labeled numeric input
	template <typename T>
	void lnbr_input (const char msg[], T& var)
	{
		PRINT(msg);
		nbr_input(var);
	}

	// for each without stop condition
	template <typename T>
	void for_each(std::list<T>& list, std::function<void(T&)> func)
	{
		for (auto it = list.begin(); it != list.end(); it++) {
			T& value = *it;
			func(value);
		}
	}

	// for each with stop condition
	template <typename T>
	void for_each(std::list<T>& list, std::function<void(T&)> func, bool break_s)
	{
		for (auto it = list.begin(); it != list.end(); it++) {
			T& value = *it;
			func(value);

			if (break_s)
				return;
		}
	}

	// for each with functional stop condition
	template <typename T>
	void for_each(std::list<T>& list, std::function<void(T&)> func, std::function <bool(T)> break_s)
	{
		for (auto it = list.begin(); it != list.end(); it++) {
			T& value = *it;
			func(value);

			if (break_s(value))
				return;
		}
	}
}

#endif
