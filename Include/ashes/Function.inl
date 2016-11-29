#pragma once

#include "Function.hpp"
#include "Engine.hpp"

namespace ash
{
namespace impl
{
namespace
{

template<typename T>
int PushArg(asIScriptContext* ctx, asUINT id, Arg arg);

template<typename Arg, typename... Args>
int PushArgs(asIScriptContext* ctx, asUINT id, Arg arg1, Args... args)
{
	int r = PushArg(ctx, id, arg1);
	if (r < 0)
		return r;

	return PushArgs(ctx, id + 1, std::forward<Args>(args)...);
}

template<>
int PushArg(asIScriptContext* ctx, asUINT id, int8_t i8) { return ctx->SetArgByte(id, i8); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, uint8_t u8) { return ctx->SetArgByte(id, u8); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, int16_t i16) { return ctx->SetArgWord(id, i16); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, uint16_t u16) { return ctx->SetArgWord(id, u16); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, int32_t i32) { return ctx->SetArgDWord(id, i32); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, uint32_t u32) { return ctx->SetArgDWord(id, u32); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, int64_t i64) { return ctx->SetArgQWord(id, i64); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, uint64_t u64) { return ctx->SetArgDWord(id, u64); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, float f32) { return ctx->SetArgFloat(id, f32); }
template<>
int PushArg(asIScriptContext* ctx, asUINT id, double f64) { return ctx->SetArgDouble(id, f64); }
template<T>
int PushArg(asIScriptContext* ctx, asUINT id, const T* ptr) { return ctx->SetArgObject(id, const_cast<T*>(ptr)); }
template<T>
int PushArg(asIScriptContext* ctx, asUINT id, T* ptr) { return ctx->SetArgObject(id, ptr); }
template<T>
int PushArg(asIScriptContext* ctx, asUINT id, const T& ref) { return ctx->SetArgObject(id, const_cast<T*>(&ref)); }
template<T>
int PushArg(asIScriptContext* ctx, asUINT id, T& ref) { return ctx->SetArgObject(id, &ref); }


}
}
}


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
Ret* ash::Function<Ret*(Args...)>::operator()(Args... args)
{
	Ret* value = nullptr;
	if (mFunc)
	{
		auto* ctx = mFunc->GetEngine()->RequestContext();
		if (call(ctx, std::forward<Args>(args)...))
			value = reinterpret_cast<Ret*>(ctx->GetAddressOfReturnValue());

		mFunc->GetEngine()->ReturnContext(ctx);
	}
	return value;
}

template<typename Ret, typename... Args>
bool ash::Function<Ret(Args...)>::call(asIScriptContext* ctx, Args... args)
{
	if ((ctx && mFunc) &&
		(ctx->Prepare(mFunc) >= 0) &&
		(mObj && ctx->SetObject(mObj) < 0) &&
		(ash::impl::PushArgs(ctx, 0, std::forward<Args>(args)...)))
		return ctx->Execute() >= 0;
	return false;
}

