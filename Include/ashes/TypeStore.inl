#pragma once

#include "TypeStore.hpp"

#include <stdexcept>

#include <angelscript.h>

ash::TypeStore::TypeDef::TypeDef(const std::string& combinedName)
{
	auto pos = combinedName.find_last_of("::");

	if (pos != std::string::npos)
	{
		Namespace = combinedName.substr(0, pos);
		Typename = combinedName.substr(pos + 2);
	}
	else
	{
		Typename = combinedName;
	}
}


ash::TypeStore* ash::TypeStore::getASHTypeStore(asIScriptEngine* eng)
{
	void* data = eng->GetUserData(ash::TypeStore::ash_TypeId);
	if (!data)
		data = eng->SetUserData(new TypeStore(eng), ash::TypeStore::ash_TypeId);

	return reinterpret_cast<TypeStore*>(data);
}

template<typename T>
std::string ash::TypeStore::getDecl() const noexcept
{
	if (mDecls.count(typeid(T)) > 0)
		return mDecls.at(typeid(T)).getCombinedName();
	return "";
}
template<typename T>
void ash::TypeStore::setDecl(const std::string& name)
{
	if (mDecls.count(typeid(T)) > 0)
		throw std::runtime_error("Trying to overwrite type");
	mDecls.emplace(typeid(T), name);
}
