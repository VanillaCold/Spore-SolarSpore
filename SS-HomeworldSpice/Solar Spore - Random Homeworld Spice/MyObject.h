#pragma once

#include <Spore\BasicIncludes.h>

#define MyObjectPtr intrusive_ptr<MyObject>

class MyObject
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("SolarSpore-HomeworldSpiceObject");
	
	MyObject();
	~MyObject();

	void Update() override;
	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	vector<uint32_t> spiceIDs{};
};
