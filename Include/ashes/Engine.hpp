#pragma once

#include <string>

class asIScriptEngine;

namespace ash
{

template<typename T>
class EnumType;
template<typename T>
class ObjectType;

class Engine
{
public:
	enum
	{
		ash_TypeId = 0xDEADBEEF
	};

	static Engine* getASHEngine(asIScriptEngine* eng);

	// Function<> getGlobalFunction();

	template<typename T>
	EnumType<T> registerEnum(const std::string& name);

	asIScriptEngine& operator*() const noexcept;
	asIScriptEngine* operator->() const noexcept;

private:
	Engine(asIScriptEngine* engine);

	asIScriptEngine* mEnginePtr;
};

}

#include "Engine.inl"
