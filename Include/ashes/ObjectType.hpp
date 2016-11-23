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

	void registerMethod();

protected:
	explicit ObjectType(Engine& eng, const std::string& name, asDWORD flags);

	Engine& getEngine() const noexcept { return mEngineRef; }
	const std::string& getName() const noexcept { return mName; }
	asDWORD getFlags() const noexcept { return mFlags; }

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
