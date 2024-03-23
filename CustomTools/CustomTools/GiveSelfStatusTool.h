#pragma once

#include <Spore\BasicIncludes.h>

#define GiveSelfStatusToolPtr intrusive_ptr<GiveSelfStatusTool>

class GiveSelfStatusTool 
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("GiveSelfStatusTool");
	
	GiveSelfStatusTool();
	~GiveSelfStatusTool();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
