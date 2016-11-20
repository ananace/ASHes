#pragma once

class asIScriptEngine;

namespace ash
{

class IRefType
{
public:
	virtual void addRef() = 0;
	virtual void release() = 0;
};

class IGCRefType : public IRefType
{
public:
	virtual int getRefCount() const noexcept = 0;

	virtual bool getGCFlag() const noexcept = 0;
	virtual void setGCFlag() const noexcept = 0;

	virtual void enumRefs(asIScriptEngine* eng) const = 0;
	virtual void releaseRefs(asIScriptEngine* eng) = 0;
};

}