#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>

class asIScriptEngine;

namespace ASH
{

	class TypeStore
	{
	public:
		static TypeStore* getTypeStore(asIScriptEngine* eng);

		template<typename Type>
		std::string getDecl() const;
		template<typename Type>
		void setDecl(const std::string& name);
		
	private:
		std::unordered_map<std::type_index, std::string> mDecls;
	};

}

#include "TypeStore.inl"
