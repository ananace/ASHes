#pragma once

class asIScriptContext;
class asIScriptFunction;
// class asIScriptWeakRef;

namespace ash
{

template<typename Ret, typename... Args>
class Function
{
public:
	Function(asIScriptFunction* func, void* object = nullptr);
	Function(const Function& copy);
	~Function();

	Function& operator=(const Function& rhs);

	Ret operator()(Args... args);
	bool call(Args... args, asIScriptContext* ctx = nullptr);

private:
	asIScriptFunction* mFunc;
	// asIScriptWeakRef* mFuncRef;
	void* mObj;
};

}

#include "Function.inl"
