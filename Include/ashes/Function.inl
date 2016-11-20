#pragma once


template<typename Ret, typename... Args>
ASH::Function::Function(asIScriptFunction* func, void* object = nullptr) :
	mFunc(func), mObj(object)
{

}

template<typename Ret, typename... Args>
ASH::Function::Function(const Function& copy)
{

}

template<typename Ret, typename... Args>
ASH::Function::~Function()
{
	if (mFunc)
		mFunc->Release();
}

template<typename Ret, typename... Args>
ASH::Function& ASH::Function::operator=(const Function& rhs)
{

}

template<typename Ret, typename... Args>
Ret ASH::Function::operator()(Args... args)
{

}

template<typename Ret, typename... Args>
bool ASH::Function::call(Args... args, asIScriptContext* ctx = nullptr)
{

}
