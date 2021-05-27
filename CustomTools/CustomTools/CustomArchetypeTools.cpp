#include "stdafx.h"
#include "CustomArchetypeTools.h"

/// AUTOGENERATED METHODS ///

int CustomArchetypeTools::AddRef() {
	return Simulator::cStrategy::AddRef();
}
int CustomArchetypeTools::Release() {
	return Simulator::cStrategy::Release();
}

const char* CustomArchetypeTools::GetName() const {
	return "CustomTools::CustomArchetypeTools";
}

bool CustomArchetypeTools::Write(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Write(stream);
}
bool CustomArchetypeTools::Read(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Read(stream);
}

/// END OF AUTOGENERATED METHODS ///
////////////////////////////////////

Simulator::Attribute CustomArchetypeTools::ATTRIBUTES[] = {
	// Add more attributes here
	// This one must always be at the end
/*	SimAttribute(CustomArchetypeTools,giventool,1),
	SimAttribute(CustomArchetypeTools,tradertool,2),*/
	Simulator::Attribute()
};

void CustomArchetypeTools::Initialize() {
	
}

void CustomArchetypeTools::Dispose() {
	
}

void CustomArchetypeTools::Update(int deltaTime, int deltaGameTime) {
	//archetype 17 = wanderer
	//App::ConsolePrintF(to_string(int(Simulator::GetPlayerEmpire()->mArchetype)).c_str());
	PropertyListPtr propList;
	if (Simulator::IsSpaceGame() && PropManager.GetPropertyList(id("testtoolsexists"), id("solarsporeconfig"), propList))
	{
		wanderAround();
		purpleSpiceDye();
		lifeBurst();
		berserkerRage();
		intergalacticDrive();
		acgenerator();
		regalshield();
		returnportal();
	}
}

bool CustomArchetypeTools::WriteToXML(Simulator::XmlSerializer* writexml)
{
	return false;
}

void CustomArchetypeTools::OnModeEntered(uint32_t previousModeID, uint32_t newModeID)
{
	if (!Simulator::IsSpaceGame() && !Simulator::IsLoadingGameMode())
	{
		giventool = false;
		tradertool = false;
		wanderertool2 = false;
		ecotool = false;
		warriortool = false;
	}
}




void CustomArchetypeTools::purpleSpiceDye()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerTrader && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("purplespicedye"),0,0 })) { tradertool = true; }
		if (tradertool == false)
		{
			ResourceKey selectedtool = { id("purplespicedye"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			tradertool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("TraderTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("purplespicedye"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			tradertool = false;
		}
	}
}

void CustomArchetypeTools::berserkerRage()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerWarrior && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("ragemode"),0,0 })) { warriortool = true; }
		if (warriortool == false)
		{
			ResourceKey selectedtool = { id("ragemode"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			warriortool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("WarriorTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("ragemode"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			warriortool = false;
		}
	}
}

void CustomArchetypeTools::intergalacticDrive()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerWanderer && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("intergalacticdrive"),0,0 })) { wanderertool2 = true; }
		if (wanderertool2 == false)
		{
			ResourceKey selectedtool = { id("intergalacticdrive"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			wanderertool2 = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("WandererTool2"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("intergalacticdrive"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			wanderertool2 = false;
		}
	}
}

void CustomArchetypeTools::wanderAround()
{
	cSpaceToolDataPtr tool;
	if (Simulator::IsSpaceGame() == true) //WanderAround
	{
		if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerWanderer)
		{
			auto inventory = SimulatorSpaceGame.GetPlayerInventory();
			if (auto test = inventory->GetTool({ id("WanderAround"),0,0 })) { giventool = true; }
			if (giventool == false)
			{
				ResourceKey selectedtool = { 0x844B3505,0,0 };
				ToolManager.LoadTool(selectedtool, tool);
				tool->mCurrentAmmoCount = 1;
				auto inventory = SimulatorSpaceGame.GetPlayerInventory();
				inventory->AddItem(tool.get());
				giventool = true;
				uint32_t eventID = UIEventLog.ShowEvent(id("WandererTool"), GroupIDs::SpacePopups);
			}
		}
		else
		{
			ResourceKey selectedtool = { 0x844B3505,0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			auto inventory = SimulatorSpaceGame.GetPlayerInventory();
			if (auto test = inventory->GetTool(selectedtool))
			{
				inventory->RemoveItem(test);
				giventool = false;
			}
			//inventory->RemoveItem(tool.get());
		}
	}
}

void CustomArchetypeTools::lifeBurst()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerEcologist && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("lifeburst"),0,0 })) { ecotool = true; }
		if (ecotool == false)
		{
			ResourceKey selectedtool = { id("lifeburst"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			ecotool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("EcoTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("lifeburst"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			ecotool = false;
		}
	}
}

void CustomArchetypeTools::acgenerator()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerScientist && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("EnergyEfficiency"),0,0 })) { scientisttool = true; }
		if (scientisttool == false)
		{
			ResourceKey selectedtool = { id("EnergyEfficiency"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			scientisttool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("TraderTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("EnergyEfficiency"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			scientisttool = false;
		}
	}
}

void CustomArchetypeTools::regalshield()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerKnight && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("regalshield"),0,0 })) { knighttool = true; }
		if (knighttool == false)
		{
			ResourceKey selectedtool = { id("regalshield"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			scientisttool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("KnightTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("regalshield"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			knighttool = false;
		}
	}
}

void CustomArchetypeTools::returnportal()
{
	cSpaceToolDataPtr tool;
	if (Simulator::GetPlayerEmpire()->mArchetype == Simulator::Archetypes::kArchetypePlayerShaman && Simulator::GetPlayerEmpire()->mStars.size() >= 30)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool({ id("ReturnPortal"),0,0 })) { shamantool = true; }
		if (shamantool == false)
		{
			ResourceKey selectedtool = { id("ReturnPortal"),0,0 };
			ToolManager.LoadTool(selectedtool, tool);
			inventory->AddItem(tool.get());
			scientisttool = true;
			uint32_t eventID = UIEventLog.ShowEvent(id("ShamanTool"), GroupIDs::SpacePopups);
		}
	}
	else
	{
		ResourceKey selectedtool = { id("ReturnPortal"),0,0 };
		ToolManager.LoadTool(selectedtool, tool);
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetTool(selectedtool))
		{
			inventory->RemoveItem(test);
			shamantool = false;
		}
	}
}
