#include "netvars.h"
#include "interfaces.h"

//antario if i remember correctly
namespace netvar_manager {
	using netvar_key_value_map = std::unordered_map< uint32_t, uintptr_t >;
	using netvar_table_map = std::unordered_map< uint32_t, netvar_key_value_map >;
	void initialize_props(netvar_table_map& table_map);

	static netvar_table_map map = {};

	uintptr_t get_net_var(const uint32_t table,
		const uint32_t prop) {
		
		if (map.empty())
			initialize_props(map);

		if (map.find(table) == map.end())
			return 0;

		netvar_key_value_map& table_map = map.at(table);
		if (table_map.find(prop) == table_map.end())
			return 0;

		return table_map.at(prop);
	}

	void add_props_for_table(netvar_table_map& table_map, const uint32_t table_name_hash, const std::string& table_name, recv_table* table, const bool dump_vars, std::map< std::string, std::map< uintptr_t, std::string > >& var_dump, const size_t child_offset = 0) {
		for (auto i = 0; i < table->props_count; ++i) {
			auto& prop = table->props[i];

			//std::cout << "Prop: " << prop.prop_name << std::endl;

			if (prop.data_table && prop.elements_count > 0) {
				//std::cout << "Prop is datatable and it not empty" << std::endl;
				if (std::string(prop.prop_name).substr(0, 1) == std::string("0"))
					continue;

				//std::cout << "Adding for table" << std::endl;
				add_props_for_table(table_map, table_name_hash, table_name, prop.data_table, dump_vars, var_dump, prop.offset + child_offset);
			}

			auto name = std::string(prop.prop_name);

			if (name.substr(0, 1) != "m" /*&& name.substr( 0, 1 ) != "b"*/)
				continue;

			const auto name_hash = fnv::hash(prop.prop_name);
			//std::cout << "Prop with name: " << name << "\tHas hash: " << name_hash << std::endl;
			const auto offset = uintptr_t(prop.offset) + child_offset;
			//std::cout << "Prop with name: " << name << "\tHas offset: " << offset << std::endl;

			try
			{
				table_map[table_name_hash][name_hash] = offset;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

			//std::cout << "Tablemap size is " << table_map.size() << std::endl;

			if (dump_vars)
			{
				//std::cout << "Dump_vars" << std::endl;
				var_dump[table_name][offset] = prop.prop_name;
			}
		}
	}

	void initialize_props(netvar_table_map& table_map) {
		const auto dump_vars = true;  //true if netvar dump

		std::map< std::string, std::map< uintptr_t, std::string > > var_dump;
		for (auto client_class = CInterfaces::get().client->get_all_classes();		//TODO: FIX
			client_class;
			client_class = client_class->Next_ptr) {
			const auto table = reinterpret_cast<recv_table*>(client_class->Recvtable_ptr);
			const auto table_name = table->table_name;
			const auto table_name_hash = fnv::hash(table_name);

			if (table == nullptr)
				continue;


			add_props_for_table(table_map, table_name_hash, table_name, table, dump_vars, var_dump);
		}
	}

	void init()
	{
		if (map.empty())
			initialize_props(map);
	}
}