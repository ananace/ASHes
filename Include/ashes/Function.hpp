#pragma once

class asIScriptContext;
class asIScriptFunction;

namespace ash
{

template<typename T>
class Function;

template<typename Ret, typename... Args>
class Function<Ret(Args...)>
{
public:
	Function(asIScriptFunction* func, void* object = nullptr);
	Function(const Function& copy);
	Function(Function&& move);
	~Function();

	Function& operator=(const Function& rhs);
	Function& operator=(Function&& rhs);

	Ret operator()(Args... args);
	bool call(asIScriptContext* ctx, Args... args);

private:
	asIScriptFunction* mFunc;
	void* mObj;
};

}

#include "Function.inl"
