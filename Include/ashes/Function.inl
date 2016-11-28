#pragma once

#include "Function.hpp"
#include "Engine.hpp"

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>::Function(asIScriptFunction* func, void* object)
	: mFunc(func)
	, mObj(object)
{
	if (mFunc)
		mFunc->AddRef();
}

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>::Function(const Function& copy)
	: mFunc(copy.mFunc)
	, mObj(copy.mObj)
{
	if (mFunc)
		mFunc->AddRef();
}

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>::Function(Function&& move)
	: mFunc(std::move(move.mFunc))
	, mObj(std::move(move.mObj))
{
	move.mFunc = nullptr;
}

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>::~Function()
{
	if (mFunc)
		mFunc->Release();
}

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>& ash::Function<Ret(Args...)>::operator=(const Function& rhs)
{
	if (this == &rhs)
		return *this;

	if (rhs.mFunc)
		rhs.mFunc->AddRef();
	if (mFunc)
		mFunc->Release();
	mFunc = rhs.mFunc;
	mObj = rhs.mObj;

	return *this;
}

template<typename Ret, typename... Args>
ash::Function<Ret(Args...)>& ash::Function<Ret(Args...)>::operator=(Function&& rhs)
{
	if (this == &rhs)
		return *this;

	if (rhs.mFunc)
		rhs.mFunc->AddRef();
	if (mFunc)
		mFunc->Release();
	mFunc = std::move(rhs.mFunc);
	if (mFunc)
		mFunc->Release();

	mObj = std::move(rhs.mObj);

	return *this;
}

template<typename... Args>
void ash::Function<void(Args...)>::operator()(Args... args)
{
	if (mFunc)
	{
		auto* ctx = mFunc->GetEngine()->RequestContext();
		call(ctx, std::forward<Args>(args)...);
		mFunc->GetEngine()->ReturnContext(ctx);
	}
}

template<typename Ret, typename... Args>
Ret ash::Function<Ret(Args...)>::operator()(Args... args)
{
	if (mFunc)
	{
		auto* ctx = mFunc->GetEngine()->RequestContext();
		if (call(ctx, std::forward<Args>(args)...))
		{

		}

		mFunc->GetEngine()->ReturnContext(ctx);
	}
}

template<typename Ret, typename... Args>
bool ash::Function<Ret(Args...)>::call(asIScriptContext* ctx, Args... args)
{

}

