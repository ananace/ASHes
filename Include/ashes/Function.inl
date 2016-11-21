#pragma once

#include "Function.hpp"
#include <angelscript.h>

template<typename Ret, typename... Args>
ash::Function<Ret, Args...>::Function(asIScriptFunction* func, void* object)
	: mFunc(func)
	, mObj(object)
{

}

template<typename Ret, typename... Args>
ash::Function<Ret, Args...>::Function(const Function& copy)
{

}

template<typename Ret, typename... Args>
ash::Function<Ret, Args...>::~Function()
{
	if (mFunc)
		mFunc->Release();
}

template<typename Ret, typename... Args>
ash::Function<Ret, Args...>& ash::Function<Ret, Args...>::operator=(const Function& rhs)
{

}

template<typename Ret, typename... Args>
Ret ash::Function<Ret, Args...>::operator()(Args... args)
{

}

template<typename Ret, typename... Args>
bool ash::Function<Ret, Args...>::call(Args... args, asIScriptContext* ctx)
{

}
