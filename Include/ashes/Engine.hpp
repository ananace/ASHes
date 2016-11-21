#pragma once

#include "EnumType.hpp"
#include "Function.hpp"
#include "ObjectType.hpp"

#include <angelscript.h>

namespace ash
{

class Engine
{
public:
	enum : asPWORD
	{
		k_EngineTypeId = 0xDEADBEEF
	};

	static Engine* getASHEngine(asIScriptEngine* eng)
	{
		void* data = eng->GetUserData(k_EngineTypeId);
		if (!data)
			data = eng->SetUserData(new Engine(eng), k_EngineTypeId);

		return reinterpret_cast<Engine*>(data);
	}

	// Function<> getGlobalFunction();

	template<typename T>
	EnumType<T> registerEnum(const std::string& name)
	{
		return EnumType<T>(*this, name);
	}


	asIScriptEngine* operator->() const noexcept
	{
		return mEnginePtr;
	}

private:
	Engine(asIScriptEngine* engine)
		: mEnginePtr(engine)
	{}

	asIScriptEngine* mEnginePtr;
};

}

#include "Engine.inl"
