#pragma once

#include "Ashes.hpp"

class asIScriptContext;
class asIScriptFunction;

namespace ASH
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
		void* mObj;
	};

}

#include "Function.inl"
