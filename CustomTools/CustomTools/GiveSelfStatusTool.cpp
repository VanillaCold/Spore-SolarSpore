#include "stdafx.h"
#include "GiveSelfStatusTool.h"

GiveSelfStatusTool::GiveSelfStatusTool()
{
}


GiveSelfStatusTool::~GiveSelfStatusTool()
{
}

// For internal use, do not modify.
int GiveSelfStatusTool::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int GiveSelfStatusTool::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* GiveSelfStatusTool::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(GiveSelfStatusTool);
	return nullptr;
}
