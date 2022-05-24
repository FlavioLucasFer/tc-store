#ifndef __TC_STORE_BASE_REPOSITORY__
#define __TC_STORE_BASE_REPOSITORY__

#include <functional>
#include <cinttypes>
#include <string>
#include <cstdio>
#include <list>
#include "lib.h"
#include "db.h"

namespace db
{
	template <typename T>
	class base_repository_t
	{
		using model_type = T;

		protected: 
			const char *table;
			const char *table_path;
			const char *fmode = "r+b";
			FILE *fp;

		private:
			void init (const char *table_path)
			{
				this->table_path = table_path;
				this->fp = fopen(table_path, "r+b");

				if (this->fp == NULL) {
					this->fp = fopen(table_path, "wb");
					this->fmode = "wb";
					#if DEBUG
						std::cout << ".sql file created to table \"" << this->table << '"';
						std::cout << " at path \"" << this->table_path << '"' << std::endl;
					#endif	
				}

				if (this->fp == NULL) {
					std::cerr << "Error: file could not be opened!";
					exit(1);
				}

				#if DEBUG
					std::cout << ".sql file \"" << this->table << '"' << " successfully loaded";
					std::cout << " from path \"" << this->table_path << '"' << std::endl;
				#endif
			}

		protected:
			void reopen_file (const char* mode)
			{
				if (this->fmode != mode) {
					freopen(this->table_path, mode, this->fp);
					this->fmode = mode;
				}
			}

			db::pk_t auto_increment ()
			{
				db::pk_t curr_id;
				fseek(this->fp, 0, SEEK_END);
				std::size_t size = ftell(this->fp);
				return size == 0 ? 1 : (size/sizeof(model_type))+1;
			}

		public:
			base_repository_t ()
			{
				std::string model_name = typeid(T).name();
				auto substrindex = model_name.find("_t");
				model_name.replace(substrindex, 2, "");
				model_name.replace(0, 1, "");
				std::string table_path = "./db/"+model_name+"s.sql";
				this->table = model_name.c_str();
				this->init(table_path.c_str());
			}

			base_repository_t (std::string table)
			{
				this->table = table.c_str();
				std::string table_path = "./db/"+table+".sql";
				this->init(table_path.c_str());
			}

			~base_repository_t ()
			{
				fclose(this->fp);
			}

		public: 
			virtual void save (model_type& model)
			{
				if (!model.get_id()) {
					model.set_id(this->auto_increment());
					fseek(this->fp, 0, SEEK_END);
				}
				else 
					fseek(this->fp, sizeof(model_type)*(model.get_id()-1), SEEK_SET);
				
				fwrite(&model, sizeof(model_type), 1, fp);
				#if DEBUG
					std::cout << "write" << std::endl;
				#endif
			}

			void save (model_type&& model) 
			{
				this->save(model);
			}

			void destroy (model_type& model)
			{
				model.destroy();
				this->save(model);
			}

			void all (std::list<model_type>& list)
			{
				rewind(this->fp);
				while (true) {
					model_type model;
					if (!fread(&model, sizeof(model_type), 1, fp))
						return;
					if (!model.is_deleted())
						list.push_back(model);
				}
			}

			virtual bool find_by_id (db::pk_t id, model_type& model)
			{
				rewind(this->fp);
				while (true) {
					model_type temp;
					if (fread(&temp, sizeof(model_type), 1, fp) == 0)
						return false;
					else if (temp.get_id() == id && !temp.is_deleted()) {
						model = temp;
						return true;
					}
				}
			}
			
			void for_each(std::function<void(model_type)> func)
			{
				rewind(this->fp);
				while (true) {
					model_type model;
					if (!fread(&model, sizeof(model_type), 1, fp))
						return;
					else if (!model.is_deleted())
						func(model);
				}
			}
	};
}

#endif
