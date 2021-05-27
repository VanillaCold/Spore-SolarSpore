#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
using namespace Simulator;
class infinitecolonies
	:public Simulator::cPlaceColonyToolStrategy
{
public:
	infinitecolonies();
	~infinitecolonies();
	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr);
	virtual bool WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors);
};