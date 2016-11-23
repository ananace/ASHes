#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>

class asIScriptEngine;

namespace ash
{

class TypeStore
{
public:
	struct TypeDef
	{
		TypeDef(const std::string& combinedName);
		std::string getCombinedName() const;

		std::string Namespace, Typename;
	};

	static TypeStore* getASHTypeStore(asIScriptEngine* eng);

	template<typename Type>
	std::string getDecl() const;
	template<typename Type>
	void setDecl(const std::string& name);

private:
	std::unordered_map<std::type_index, TypeDef> mDecls;
};

}

#include "TypeStore.inl"
