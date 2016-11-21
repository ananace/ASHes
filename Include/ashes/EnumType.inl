#pragma once

#include "Engine.hpp"
#include "EnumType.hpp"

template<typename T>
ash::EnumType::Value& ash::EnumType::Value::operator=(int value)
{
	auto& eng = mType->mEngineRef;

	int r = eng->RegisterEnumValue(mType->mName.c_str(), mName.c_str(), value);

	return *this;
}

template<typename T>
ash::EnumType::Value::Value(EnumType* type, const std::string& name)
	: mType(type)
	, mName(name)
{
}

template<typename T>
ash::EnumType::EnumType(Engine& engine, const std::string& name)
	: mEngineRef(engine)
	, mName(name)
{
	auto& eng = mEngineRef;

	int r = eng->RegisterEnum(mName.c_str());
}

template<typename T>
ash::EnumType::Value ash::EnumType::operator[](const std::string& name)
{
	return Value(this, name);
}
