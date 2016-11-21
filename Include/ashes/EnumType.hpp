#pragma once

#include <string>

namespace ash
{

class Engine;

template<typename T>
class EnumType
{
public:
	class Value
	{
	public:
		Value& operator=(int value);

	private:
		Value(EnumType* type, const std::string& name);

		EnumType* mType;
		std::string mName;

		friend class EnumType;
	};

	EnumType(Engine& engine, const std::string& name);

	EnumType(const EnumType& copy) = default;
	EnumType(EnumType&& move) = default;
	~EnumType() noexcept = default;

	Value operator[](const std::string& name);

private:
	Engine& mEngineRef;
	std::string mName;

	friend class Value;
};

}

