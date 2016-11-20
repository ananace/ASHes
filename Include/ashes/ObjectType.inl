#pragma once

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
void ash::ValueType<T>::registerDefaults<0>() {}

template<typename T>
void ash::ValueType<T>::registerDefaults<asOBJ_APP_CLASS_A>()
{

}

template<typename T>
void ash::ValueType<T>::registerDefaults<asOBJ_APP_CLASS_C>()
{
	auto* ptr = mEngineRef.getEngine();

	int r = ptr->RegisterObjectBehaviour(mName.c_str(), asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(defaultConstructor<T>), asCALL_CDECL_OBJLAST);
}

template<typename T>
void ash::ValueType<T>::registerDefaults<asOBJ_APP_CLASS_D>()
{
	auto* ptr = mEngineRef.getEngine();

	int r = ptr->RegisterObjectBehaviour(mName.c_str(), asBEHAVE_DESTRUCT, "void f()", asFUNCTION(defaultConstructor<T>), asCALL_CDECL_OBJLAST);
}

template<typename T>
void ash::ValueType<T>::registerDefaults<asOBJ_APP_CLASS_K>()
{

}

template<typename T, size_t P>
void ash::ValueType<T>::registerDefaults()
{
	registerDefaults<P & asOBJ_APP_CLASS_A>();
	registerDefaults<P & asOBJ_APP_CLASS_C>();
	registerDefaults<P & asOBJ_APP_CLASS_D>();
	registerDefaults<P & asOBJ_APP_CLASS_K>();
}

template<typename T>
void ash::RefType<T>::registerDefaults<0>() {}

template<typename T>
void ash::RefType<T>::registerDefaults<asOBJ_APP_CLASS_C>()
{
	auto* ptr = mEngineRef.getEngine();

	int r = ptr->RegisterObjectBehaviour(mName.c_str(), asBEHAVE_FACTORY, (mName + "@ f()").c_str(), asFUNCTION(defaultFactory<T>), asCALL_CDECL);
}

template<typename T, size_t P>
void ash::RefType<T>::registerDefaults()
{
	registerDefaults<P & asOBJ_APP_CLASS_C>();

	if ((getFlags() & asOBJ_NOCOUNT) != 0)
		return;

	auto* ptr = mEngineRef.getEngine();

	int r = ptr->RegisterObjectBehaviour(mName.c_str(), asBEHAVE_ADDREF, "void f()", asMETHODPR(T, addRef, (), void), asCALL_THISCALL);
	int r = ptr->RegisterObjectBehaviour(mName.c_str(), asBEHAVE_RELEASE, "void f()", asMETHODPR(T, release, (), void), asCALL_THISCALL);

	if (std::is_base_of<T, IGCRefType>())
	{

	}
}