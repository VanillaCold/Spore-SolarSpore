#include "stdafx.h"
#include "SetupModStrategies.h"

#include "vehicletest.h"
#include "ToSol.h"
#include "SpawnVehicle.h"
#include "ChangeSpecies.h"
#include "EraseSpecies.h"
#include "MySystem.h"
#include "StaffofDeath.h"
#include "ConvertPlanet.h"
#include "GroxColony.h"
//#include "ChangeCaptain.h"
#include "SetPlanetType.h"
#include "infinitecolonies.h"
#include "PlanetDebuster.h"
//#include "SystemCount.h"
#include "RandomTool.h"
#include "ContactHomeworld.h"
#include "WanderingPortal.h"
#include "LifeBurst.h"
#include "SpiceDye.h"
#include "BerserkerRage.h"
#include "IntergalacticDrive.h"
#include "Detente.h"
#include "Capacitor.h"
#include "RegalShield.h"
#include "AmmoCreator.h"
#include "ReturnPortal.h"
#include "StarKiller.h"
#include "cSSArchetypeToolManager.h"
#include "ToggleSSDebug.h"
#include "MySystem.h"
#include "cSSResearchManager.h"
#include "GetResearchData.h"
#include "cSSArchetypeWeaponSystem.h"
#include "GoToHome.h";

#include "DamageMultiplierProjectile.h"
#include "DelayedBeamWeapon.h"
#include "cSSStatusEffectManager.h"
#include "PoisonProjectileWeapon.h"

#include "cSSStatusEffectManager.h"

void SetupModStrategies::SetupStrategies()
{
	//Add tools
	ToolManager.AddStrategy(new ToSol(), id("ToSol"));
	ToolManager.AddStrategy(new SpawnVehicle(), id("SpawnVehicle"));
	ToolManager.AddStrategy(new ChangeSpecies(), id("ChangeSpecies"));
	ToolManager.AddStrategy(new EraseSpecies(), id("EraseSpecies"));
	ToolManager.AddStrategy(new ConvertPlanet(), id("ConvertPlanet"));
	ToolManager.AddStrategy(new GroxColony(), id("GroxColony"));
	ToolManager.AddStrategy(new StaffofDeath(), id("StaffOfDeath"));
	ToolManager.AddStrategy(new infinitecolonies(), id("InfiniteColonies"));
	ToolManager.AddStrategy(new PlanetDebuster(), id("PlanetDebuster"));
	ToolManager.AddStrategy(new RandomTool(), id("RandomTool"));
	ToolManager.AddStrategy(new WanderingPortal(), id("WanderingPortal"));
	ToolManager.AddStrategy(new LifeBurst(), id("LifeBurst"));
	ToolManager.AddStrategy(new SpiceDye(), id("SpiceDye"));
	ToolManager.AddStrategy(new BerserkerRage(), id("BerserkerRage"));
	ToolManager.AddStrategy(new IntergalacticDrive(), id("IntergalacticDrive"));
	ToolManager.AddStrategy(new Detente(), id("Detente"));
	ToolManager.AddStrategy(new RegalShield(), id("RegalShield"));
	ToolManager.AddStrategy(new capacitor(), id("EnergyEfficiency"));
	ToolManager.AddStrategy(new AmmoCreator(), id("AmmoCreator"));
	ToolManager.AddStrategy(new ReturnPortal(), id("ReturnPortal"));
	ToolManager.AddStrategy(new StarKiller(), id("Starkiller"));
	

	
	//Add generalised tools
	ToolManager.AddStrategy(new DelayedBeamWeapon(), DelayedBeamWeapon::STRATEGY_ID);
	ToolManager.AddStrategy(new DamageMultiplierProjectile(), DamageMultiplierProjectile::STRATEGY_ID);
	ToolManager.AddStrategy(new PoisonProjectileWeapon(), PoisonProjectileWeapon::STRATEGY_ID);

	//Add debug cheats
#ifdef _DEBUG
	{
		CheatManager.AddCheat("spawnvehicle", new vehicletest());
		//CheatManager.AddCheat("changecaptain", new ChangeCaptain());
		CheatManager.AddCheat("setPlanetType", new SetPlanetType());
		//	CheatManager.AddCheat("empireInfo", new SystemCount());
		CheatManager.AddCheat("contactHomeworld", new ContactHomeworld());
		CheatManager.AddCheat("togglessdebug", new ToggleSSDebug());
		CheatManager.AddCheat("gth", new GoToHome());
		new GetResearchData();
	}
#endif

	//Add simulator strategy (to-do: make strategy obsolete and remove it)
	SimulatorSystem.AddStrategy(new MySystem(), MySystem::NOUN_ID);
	SimulatorSystem.AddStrategy(new cSSArchetypeWeaponSystem, cSSArchetypeWeaponSystem::NOUN_ID);
	SimulatorSystem.AddStrategy(new cSSStatusEffectManager, cSSStatusEffectManager::NOUN_ID);
	
	//Add research strategy; this one is NOT to be obsolete.
	if (PropManager.HasPropertyList(id("ss_enableresearch"), id("solarsporeconfig")))
	{
		SimulatorSystem.AddStrategy(new cSSResearchManager(), cSSResearchManager::NOUN_ID);
	}
	//Add archetype tools
	if (PropManager.HasPropertyList(id("sstoolsexist"), id("solarsporeconfig")))
	{
		try
		{
			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerTrader,
				id("purplespicedye"),
				id("TraderTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerWarrior,
				id("ragemode"),
				id("WarriorTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerWanderer,
				id("intergalacticdrive"),
				id("WandererTool2")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerEcologist,
				id("lifeburst"),
				id("EcoTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerScientist,
				id("EnergyEfficiency"),
				id("ScientistTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerKnight,
				id("regalshield"),
				id("KnightTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerShaman,
				id("ReturnPortal"),
				id("ShamanTool")
			));

			SSConsequenceToolManager.AddArchetypeTool(ArchetypeTool(
				Simulator::Archetypes::kArchetypePlayerDiplomat,
				id("Detente")
			));

		}
		catch (std::exception except)
		{
			const char* text = except.what();
			wstring report;
			report.assign_convert(text);
			MessageBox(NULL, report.c_str(), LPCWSTR(u"Error adding tool"), 0x00000010L);
		}
	}
}
