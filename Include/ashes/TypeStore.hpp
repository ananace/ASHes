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
	enum
	{
		ash_TypeId = 0xBEEFBEEF
	}

	struct TypeDef
	{
		TypeDef(const std::string& combinedName);
		std::string getCombinedName() const noexcept;

		std::string Namespace, Typename;
	};

	static TypeStore* getASHTypeStore(asIScriptEngine* eng);

	template<typename Type>
	std::string getDecl() const noexcept;
	template<typename Type>
	void setDecl(const std::string& name);

private:
	std::unordered_map<std::type_index, TypeDef> mDecls;
};

}

#include "TypeStore.inl"
