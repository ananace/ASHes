#pragma once

#include "Engine.hpp"
#include "ObjectType.hpp"

namespace ash
{
namespace priv
{
template<typename T>
void defaultConstructor(T* mem)
{
	new (mem)T();
}
template<typename T>
T* defaultFactory()
{
	return new T();
}
template<typename T>
void defaultDestructor(T* obj)
{
	obj->~T();
}
}
}

template<typename T>
ash::priv::ObjectType<T>::ObjectType(Engine& eng, const std::string& name, asDWORD flags)
	: mEngineRef(eng)
	, mName(name)
	, mFlags(flags)
{
	auto* ptr = mEngineRef.getEngine();

	int r = ptr->RegisterObjectType(mName.c_str(), sizeof(T), flags);
}

template<typename T>
ash::ValueType::ValueType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ObjectType(eng, name, asOBJ_VALUE | extraFlags | asGetTypeTraits<T>())
{}

template<typename T>
ash::RefType::ValueType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ObjectType(eng, name, asOBJ_REF | extraFlags)
{}
