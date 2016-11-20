#pragma once

#include "Engine.hpp"
#include "EnumType.hpp"
#include "IRefType.hpp"

#include <type_traits>

namespace ash
{

namespace priv
{

template<typename T>
class ObjectType
{
public:
	virtual ~ObjectType() noexcept = default;

	template<size_t P = asOBJ_APP_CLASS_CDAK>
	virtual void registerDefaults() = 0;

	void registerMethod();

protected:
	explicit ObjectType(Engine& eng, const std::string& name, asDWORD flags)
	{
		auto* ptr = mEngineRef.getEngine();

		int r = ptr->RegisterObjectType(mName.c_str(), sizeof(T), flags);
	}

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
	ValueType(Engine& eng, const std::string& name, asDWORD extraFlags = 0)
		: ObjectType(eng, name, asOBJ_VALUE | extraFlags | asGetTypeTraits<T>())
	{}

	template<size_t P = asOBJ_APP_CLASS_CDAK>
	virtual void registerDefaults() = 0;
};

template<typename T>
class RefType : public priv::ObjectType<T>
{
static_assert(std::is_base_of<T, ash::IRefType>(), "Must be a reference type");

public:
	RefType(Engine& eng, const std::string& name, asDWORD extraFlags = 0)
		: ObjectType(eng, name, asOBJ_REF | extraFlags)
	{}

	template<size_t P = asOBJ_APP_CLASS_C>
	virtual void registerDefaults() = 0;
};

}

#include "ObjectType.inl"
