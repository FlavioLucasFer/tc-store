#ifndef __TC_STORE_DB__
#define __TC_STORE_DB__

#include <cinttypes>
#include <cstring>

#define GENERATE_DB_TYPE_MACRO(TYPE, VAR) \
	using VAR##_t = TYPE; \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR(TYPE VAR) \
		{ \
			this->VAR = VAR; \
		}

#define GENERATE_DB_TYPE_MACRO_RO(TYPE, VAR) \
	using VAR##_t = TYPE; \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		}

#define INTEGER(VAR) GENERATE_DB_TYPE_MACRO(db::integer_t, VAR)
#define INTEGER_RO(VAR) GENERATE_DB_TYPE_MACRO_RO(db::integer_t, VAR)
#define UINTEGER(VAR) GENERATE_DB_TYPE_MACRO(db::uint_t, VAR)
#define UINTEGER_RO(VAR) GENERATE_DB_TYPE_MACRO(db::uint_t, VAR)
#define NUMERIC(VAR) GENERATE_DB_TYPE_MACRO(db::numeric_t, VAR)
#define NUMERIC_RO(VAR) GENERATE_DB_TYPE_MACRO_RO(db::numeric_t, VAR)

#define PK(VAR) \
	using VAR##_t = db::pk_t; \
	private: \
		db::pk_t VAR = 0; \
	public: \
		inline db::pk_t get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR(db::pk_t VAR) \
		{ \
			if (!this->VAR) \
				this->VAR = VAR; \
		}

#define VARCHAR(VAR, LENGTH) \
	using VAR##_t = db::varchar_t; \
	private: \
		char VAR[LENGTH]; \
	public: \
		inline db::varchar_t get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR(db::varchar_t VAR) \
		{ \
			strcpy(this->VAR, VAR); \
		}

#define VARCHAR_RO(VAR, LENGTH) \
	using VAR##_t = db::varchar_t; \
	private: \
		char VAR[LENGTH]; \
	public: \
		inline db::varchar_t get_##VAR () \
		{ \
			return this->VAR; \
		}

#define DELETED_FLAG \
	private: \
		bool deleted = false; \
	public: \
		inline void destroy () \
		{ \
			this->deleted = true; \
		} \
		inline void restore () \
		{ \
			this->deleted = false; \
		} \
		inline bool is_deleted () \
		{ \
			return this->deleted; \
		}

namespace db
{
	using pk_t = uint64_t;
	using varchar_t = const char*;
	using integer_t = int;
	using char_t = char*;
	using numeric_t = double;
	using uint_t = unsigned int;
}

#endif