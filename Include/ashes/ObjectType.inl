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

template<typename T, typename C, typename F>
int ash::priv::ObjectType<T>::registerMethod<C::F>(const std::string& methodName);
{
	// Type inferrence
	asDWORD conv = asCALL_THISCALL;
	std::string decl = "";

	return registerMethodEx(&C::F, conv, decl);
}

template<typename T, typename F>
int ash::priv::ObjectType<T>::registerMethod<F>(const std::string& methodName);
{
	// Type inferrence
	asDWORD conv = asCALL_CDECL;
	std::string decl = "";

	return registerMethodEx(&F, conv, decl);
}

template<typename T>
template<typename Functor>
int ash::priv::ObjectType<T>::registerMethodEx(Functor&& func, asDWORD conv, const std::string& decl)
{
	auto& eng = getEngine();

	// TODO: Functor / delegate wrapper
	// TODO: Functor store
	// void Functor::call(T* obj, Args... args);
	return eng->RegisterObjectMethod(mName.c_str(), decl.c_str(), asMETHOD(Functor, call), asCALL_THISCALL_OBJFIRST, &func);
}

template<typename T>
ash::ValueType<T>::ValueType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ash::priv::ObjectType<T>(eng, name, asOBJ_VALUE | extraFlags | asGetTypeTraits<T>())
{}

template<typename T>
ash::RefType<T>::RefType(Engine& eng, const std::string& name, asDWORD extraFlags)
	: ash::priv::ObjectType<T>(eng, name, asOBJ_REF | extraFlags)
{}
