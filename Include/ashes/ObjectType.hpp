#pragma once

#include "IRefType.hpp"

#include <type_traits>

namespace ash
{

class Engine;

namespace priv
{

template<typename T>
class ObjectType
{
public:
	virtual ~ObjectType() noexcept = default;

	template<typename C, typename F>
	int registerMethod<C::F>(const std::string& methodName);
	template<typename F>
	int registerMethod<F>(const std::string& methodName);

	template<typename C, typename F>
	int registerMethod<C::F>(const std::string& decl, asDWORD conv);
	template<typename F>
	int registerMethod<F>(const std::string& decl, asDWORD conv);

	Engine& getEngine() const noexcept { return mEngineRef; }
	const std::string& getName() const noexcept { return mName; }
	asDWORD getFlags() const noexcept { return mFlags; }

protected:
	explicit ObjectType(Engine& eng, const std::string& name, asDWORD flags);

	template<typename Functor>
	virtual int registerMethodEx(Functor&& func, const std::string& method, asDWORD flags, const std::string& decl);

private:
	Engine& mEngineRef;
	std::string mName;
	asDWORD mFlags;
};

}

template<typename T>
class ValueType : public priv::ObjectType<T>
{
public:
	ValueType(Engine& eng, const std::string& name, asDWORD extraFlags = 0);
};

template<typename T>
class RefType : public priv::ObjectType<T>
{
static_assert(std::is_base_of<T, ash::IRefType>(), "Must be a reference type");

public:
	RefType(Engine& eng, const std::string& name, asDWORD extraFlags = 0);
};

}

#include "ObjectType.inl"
