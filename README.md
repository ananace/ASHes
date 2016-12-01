ASHes
=====

AngelScript Helper library.

This library contains objects and methods to simplify the registering and usage of an Angelscript application interface.


Usage
-----

```c++

#include <ashes/ashes.hpp>

class DataType
{
public:
	struct POD
	{
		int data;
	};

	enum Value
	{
		One = 1,
		Two,
		Three,
		Five = 5
	};

	DataType() = default;
	DataType(int data);
	DataType(const DataType&) = default;
	~DataTYpe() = default;

	DataType& operator=(const DataType&) = default;

	void init();

	void setData(int data);
	int getData() const;

	Value getValue() const;

	POD toPod() const;
};

void constructData(void* mem)
{
	new(mem) DataType();
}
void constructDataVal(void* mem, int data)
{
	new(mem) DataType(data);
}
void constructDataCopy(void* mem, const DataType& copy)
{
	new(mem) DataType(copy);
}
void destructData(DataType* mem)
{
	mem->~DataType();
}

void registerAS(asIScriptEngine* eng)
{
	int r = eng->RegisterObjectType("DataType", sizeof(DataType), asOBJ_VALUE | asTypeGetInfo<DataType>()); assert(r >= 0);
	r = eng->RegisterObjectType("DataType::POD", sizeof(DataType::POD), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
	r = eng->RegisterEnum("DataType::Value"); assert(r >= 0);
	r = eng->RegisterEnumValue("DataType::Value", "One", DataType::One); assert(r >= 0);
	r = eng->RegisterEnumValue("DataType::Value", "Two", DataType::Two); assert(r >= 0);
	r = eng->RegisterEnumValue("DataType::Value", "Three", DataType::Three); assert(r >= 0);
	r = eng->RegisterEnumValue("DataType::Value", "Five", DataType::Five); assert(r >= 0);

	r = eng->RegisterObjectProperty("DataType::POD", "int data", asOFFSET(DataType::POD, data)); assert(r >= 0);

	r = eng->RegisterObjectBehaviour("DataType", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructData), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = eng->RegisterObjectBehaviour("DataType", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(constructDataVal), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = eng->RegisterObjectBehaviour("DataType", asBEHAVE_CONSTRUCT, "void f(DataType&in)", asFUNCTION(constructDataCopy), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = eng->RegisterObjectBehaviour("DataType", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destructData), asCALL_CDECL_OBJFIRST); assert(r >= 0);

	r = eng->RegisterObjectMethod("DataType", "DataType& opAssign(DataType&in)", asMETHOD(DataType, operator=), asCALL_THISCALL); assert(r >= 0);

	r = eng->RegisterObjectMethod("DataType", "void init()", asMETHOD(DataType, init), asCALL_THISCALL); assert(r >= 0);
	r = eng->RegisterObjectMethod("DataType", "void set_Data(int)", asMETHOD(DataType, setData), asCALL_THISCALL); assert(r >= 0);
	r = eng->RegisterObjectMethod("DataType", "int get_Data() const", asMETHOD(DataType, getData), asCALL_THISCALL); assert(r >= 0);

	r = eng->RegisterObjectMethod("DataType", "DataType::Value get_Value() const", asMETHOD(DataType, getValue), asCALL_THISCALL); assert(r >= 0);

	r = eng->RegisterObjectMethod("DataType", "DataType::POD get_POD() const", asMETHOD(DataType, toPod), asCALL_THISCALL); assert(r >= 0);


	// Function call
	auto* ctx = eng->RequestContext(); assert(ctx);

	auto* type = eng->GetTypeInfoByName("DataType"); assert(type);
	auto* obj = eng->CreateScriptObject(type); assert(obj);
	auto* func = obj->GetMethodByName("get_POD"); assert(func);

	r = ctx->Prepare(func); assert(r >= 0);
	r = ctx->SetObject(obj); assert(r >= 0);

	r = ctx->Execute(); assert(r >= 0);

	DataType::POD value = *reinterpret_cast<DataType::POD*>(ctx->GetAddressOfReturnValue());

	eng->ReturnContext(ctx);
}

void registerASH(ash::Engine& eng)
{
	auto dt = eng.registerValueType<DataType>("DataType");
	auto pod = eng.registerValueType<DataType::POD>("DataType::POD", asOBJ_POD);
	auto value = eng.registerEnum<DataType::Value>("DataType::Value");

	value["One"] = DataType::One;
	value["Two"] = DataType::Two;
	value["Three"] = DataType::Three;
	value["Five"] = DataType::Five;

	pod.registerProperty<DataType::POD::data>("data");

	dt.registerCDAK();
	dt.registerConstructor<int>();
	
	dt.registerMethod<DataType::init>("init");
	dt.registerMethod<DataType::setData>("set_Data");
	dt.registerMethod<DataType::getData>("get_Data");
	dt.registerMethod<DataType::getValue>("get_Value");
	dt.registerMethod<DataType::toPod>("get_POD");
}


```
