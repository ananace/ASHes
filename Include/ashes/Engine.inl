#pragma once

#include "Engine.hpp"
#include "EnumType.hpp"
#include "Function.hpp"
#include "ObjectType.hpp"

#include <angelscript.h>

ash::Engine::Engine(asIScriptEngine* engine)
	: mEnginePtr(engine)
{}

ash::Engine* ash::Engine::getASHEngine(asIScriptEngine* eng)
{
	void* data = eng->GetUserData(ash::Engine::ash_TypeId);
	if (!data)
		data = eng->SetUserData(new Engine(eng), ash::Engine::ash_TypeId);

	return reinterpret_cast<Engine*>(data);
}

template<typename T>
ash::EnumType<T> ash::Engine::registerEnum(const std::string& name)
{
	return EnumType<T>(*this, name);
}

asIScriptEngine& ash::Engine::operator*() const noexcept
{
	return *mEnginePtr;
}

asIScriptEngine* ash::Engine::operator->() const noexcept
{
	return mEnginePtr;
}
