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
ash::priv::ObjectType<T>::ObjectType(ash::Engine& engine, const std::string& name, asDWORD flags)
	: mEngineRef(engine)
	, mName(name)
	, mFlags(flags)
{
	auto& eng = *mEngineRef;

	int r = eng.RegisterObjectType(mName.c_str(), sizeof(T), flags);
}

template<typename T>
ash::ValueType<T>::ValueType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ash::priv::ObjectType<T>(eng, name, asOBJ_VALUE | extraFlags | asGetTypeTraits<T>())
{}

template<typename T>
ash::RefType<T>::RefType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ash::priv::ObjectType<T>(eng, name, asOBJ_REF | extraFlags)
{}
