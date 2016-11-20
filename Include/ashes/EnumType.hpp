#pragma once

#include "Engine.hpp"
#include <string>

namespace ash
{

template<typename T>
class EnumType
{
public:
	class Value
	{
	public:
		Value& operator=(int value)
		{
			auto* ptr = mType->mEngineRef.getEngine();

			int r = ptr->RegisterEnumValue(mType->mName.c_str(), mName.c_str(), value);

			return *this;
		}

	private:
		Value(EnumType* type, const std::string& name);

		EnumType* mType;
		std::string mName;

		friend class EnumType;
	};

	EnumType(Engine& engine, const std::string& name)
		: mEngineRef(engine)
		, mName(name)
	{
		auto* ptr = mEngineRef.getEngine();

		int r = ptr->RegisterEnum(mName.c_str());
	}

	EnumType(const EnumType& copy) = default;
	EnumType(EnumType&& move) = default;
	~EnumType() const noexcept = default;

	Value operator[](const std::string& name)
	{
		return Value(this, name);
	}

private:
	Engine& mEngineRef;
	std::string mName;

	friend class Value;
};

}

