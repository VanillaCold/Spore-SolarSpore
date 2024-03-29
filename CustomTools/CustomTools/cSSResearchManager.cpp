#include "stdafx.h"
#include "cSSResearchManager.h"
#include "CloseResearchMenu.h"
#include "cResearchWinProc.h"
#include "cResearchButtonWinProc.h"
#include <Spore\UTFWin\WinTreeView.h>
#include <Spore\UTFWin\IButton.h>

/// AUTOGENERATED METHODS ///

int cSSResearchManager::AddRef() {
	return Simulator::cStrategy::AddRef();
}
int cSSResearchManager::Release() {
	return Simulator::cStrategy::Release();
}

const char* cSSResearchManager::GetName() const {
	return "CustomTools::cSSResearchManager";
}

bool cSSResearchManager::Write(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Write(stream);
}
bool cSSResearchManager::Read(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Read(stream);
}

bool cSSResearchManager::WriteToXML(Simulator::XmlSerializer* writexml)
{
	return false;
}


/// END OF AUTOGENERATED METHODS ///
////////////////////////////////////

Simulator::Attribute cSSResearchManager::ATTRIBUTES[] = {
	// Add more attributes here
	// This one must always be at the end
	SimAttribute(cSSResearchManager,mResearchPoints,1),
	Simulator::Attribute()
};

void cSSResearchManager::Initialize() {
	mResearchPoints = 0;
	sInstance = this;
	mpUIlayout = nullptr;
	SetupResearches();
}

void cSSResearchManager::Dispose() {
	
}

void cSSResearchManager::Update(int deltaTime, int deltaGameTime)  //Executed every frame
{
	if (Simulator::IsSpaceGame()) //If we're in the space stage... (adventures do not count)
	{
		float length = ((deltaGameTime) / 1000.0f) * (1.25*logf(Simulator::SpacePlayerData::Get()->mPlayerColonies.size()+1)) / 60; //Get the passive income of research points
		mResearchPoints += length; //and increase the points by said passive income.

		/*if (mpPointsCaption) //If the points caption is present,
		{
			float points = mResearchPoints;
			string16 cap;
			cap.assign_convert(to_string(int(floor(points))));
			cap = u"\u268C " + cap;
			mpPointsCaption->SetCaption(cap.c_str());
			//SporeDebugPrint("%f", mResearchPoints);
		}*/

		if (mWindowOffset != 0 && mpUIlayout)
		{
			auto window = mpUIlayout->FindWindowByID(0xFFFFFFFF, false);
			float offset2 = (((mWindowOffset * -1) + 1) / 8); //max((((windowOffset * -1) + 1) / 8), 1.0)
			mWindowOffset = mWindowOffset + offset2;

			UTFWin::IWindow* parentWindow = window->GetParent();
			Math::Rectangle rec = parentWindow->GetArea();
			window->SetArea(Math::Rectangle(rec.right / 2 - (801 / 2), (rec.bottom / 2 - (602 / 2)) + mWindowOffset, rec.right / 2 + (801 / 2), (rec.bottom / 2 + (602 / 2)) + mWindowOffset));
		}
	}
	else
	{
		if (mpUIlayout)
		{
			CloseResearchUI(false);
		}
	}
}

cSSResearchManager* cSSResearchManager::Get()
{
	return sInstance;
}

bool cSSResearchManager::CheckResearchExists(uint32_t resID)
{
	/*for (int i = 0; i < mResearchTypes.size(); i++)
	{
		if (mResearchTypes[i].mResearchID == resID)
		{
			return true;
		}
	}*/
	if (mResearchTypes.find(resID) != mResearchTypes.end())
	{
		return true;
	}
	return false;
}

bool cSSResearchManager::HasResearched(uint32_t resID)
{
	ResearchType& res = GetResearch(resID);
	if (res)
	{
		if (SimulatorSpaceGame.GetPlayerInventory()->HasTool({ res.mToolID,0,0 }))
		{
			return true;
		}
	}
	return false;
}

bool cSSResearchManager::ResearchItem(uint32_t resID, string& outError)
{
	
	if (ResearchType& res = GetResearch(resID))
	{
		auto inv = SimulatorSpaceGame.GetPlayerInventory();
		if (inv->HasTool({ res.mToolID,0,0 }))
		{
			outError = "Already researched.";
			return false;
		}

		for each (uint32_t priorID in res.mPriorResearches)
		{
			if (!HasResearched(priorID))
			{
				LocalizedString str = LocalizedString(id("SS_Research"), 0x05);
				HintManager.ShowHint(id("NoPriorResearch"));
				outError.assign_convert(str.GetText());
				return false;
			}
		}

		if (mResearchPoints < res.mRequiredPoints)
		{
			LocalizedString str = LocalizedString(id("SS_Research"), 0x04);
			HintManager.ShowHint(id("NoResourcePoints"));
			outError.assign_convert(str.GetText());
			return false;
		}
		
		
		cSpaceToolDataPtr pTool;
		if (ToolManager.LoadTool({ res.mToolID,0,0 }, pTool))
		{
			inv->AddItem(pTool.get());
			mResearchPoints -= res.mRequiredPoints;
			return true;
		}
	}
	return false;
}

bool cSSResearchManager::CanResearch(uint32_t resID, string& outError)
{
	if (ResearchType& res = GetResearch(resID))
	{
		auto inv = SimulatorSpaceGame.GetPlayerInventory();
		if (inv->HasTool({ res.mToolID,0,0 }))
		{
			outError = "Already researched.";
			return false;
		}

		if (mResearchPoints < res.mRequiredPoints)
		{
			LocalizedString str = LocalizedString(id("SS_Research"), 0x04);
			outError.assign_convert(str.GetText());
			return false;
		}
		for each (uint32_t priorID in res.mPriorResearches)
		{
			if (!HasResearched(priorID))
			{
				LocalizedString str = LocalizedString(id("SS_Research"), 0x05);
				outError.assign_convert(str.GetText());
				return false;
			}
		}

		return true;
	}
	return false;
}

ResearchType& cSSResearchManager::GetResearch(uint32_t resID)
{
	if (mResearchTypes.find(resID) != mResearchTypes.end())
	{
		return mResearchTypes[resID];
	}
	return ResearchType(0);
}

// UI functions

bool cSSResearchManager::OpenResearchUI(bool animation)
{
	if (!mpPointsCaption)
	{
		if (!mpUIlayout)
		{
			mpUIlayout = new UTFWin::UILayout();
		}

		if (mpUIlayout->LoadByID(id("ResearchScreen")))
		{
			mpUIlayout->SetVisible(true);
			mpUIlayout->SetParentWindow(WindowManager.GetMainWindow());
			auto window = mpUIlayout->FindWindowByID(0xFFFFFFFF, false);
			window->SetSize(801.0F, 602.0F);
			WindowManager.GetMainWindow()->SendToBack(mpUIlayout->GetContainerWindow());

			Math::Rectangle rec = window->GetParent()->GetArea();

			if (animation)
			{
				mWindowOffset = (rec.bottom / 2 + (602 / 2));
			}
			else
			{
				mWindowOffset = 0;
			}

			window->SetArea(Math::Rectangle(rec.right / 2 - (801 / 2), (rec.bottom / 2 - (602 / 2)) + mWindowOffset, rec.right / 2 + (801 / 2), (rec.bottom / 2 + (602 / 2)) + mWindowOffset));

			auto closeButton = mpUIlayout->FindWindowByID(id("closebutton"));
			closeButton->AddWinProc(new CloseResearchMenu());

			auto resButton = mpUIlayout->FindWindowByID(id("ResearchButton"));
			resButton->AddWinProc(new cResearchWinProc());

			mpPointsCaption = mpUIlayout->FindWindowByID(id("RSPointCounter"));

			auto nameCaption = mpUIlayout->FindWindowByID(id("ResName"));
			nameCaption->SetCaption(u"");

			auto descCaption = mpUIlayout->FindWindowByID(id("ResDescr"));
			descCaption->SetCaption(u"");

			auto inventoryWindow = mpUIlayout->FindWindowByID(id("Inventory"), true);

			//scrollWindow = nullptr;
			//UI::ScrollFrameVertical::Create(u"PlayerInvPart", scrollWindow);
			
			//inventoryWindow->AddWindow(scrollWindow.get());

			LoadUIItems();

			return true;
		}
	}
	
	return false;
}

bool cSSResearchManager::CloseResearchUI(bool animation)
{
	if (mpUIlayout)
	{
		auto openButton = WindowManager.GetMainWindow()->FindWindowByID(id("OpenResearchButton"));
		if (openButton->GetState() == 13 || openButton->GetState() == 21 || openButton->GetState() == 29 || openButton->GetState() == 31 || openButton->GetState() == 25 || openButton->GetState() == 15 || openButton->GetState() == 9)
		{
			openButton->SetState(9);
		}
		else
		{
			openButton->SetState(1);
		}
		openButton->SetTextFontID(0);
		mWindowOffset = 0;
		WindowManager.GetMainWindow()->RemoveWindow(mpUIlayout->FindWindowByID(0xFFFFFFFF, false));
		mpPointsCaption = false;
		mpUIlayout = nullptr;
		return true;
	}
	return false;
}



void cSSResearchManager::LoadUIItems()
{
	//auto inventoryWindow = scrollWindow.get();//mpUIlayout->FindWindowByID(id("Inventory"), true);
	auto inventoryWindow = mpUIlayout->FindWindowByID(id("Inventory"), true);
	int i = 0;
	
	vector<ResearchType> validResearches;
	vector<ResearchType> invalidResearches;

	for (auto it = mResearchTypes.begin(); it != mResearchTypes.end(); it++)
	{
		string error;
		if (CanResearch(it.mpNode->mValue.second.mToolID,error))
		{
			validResearches.push_back(it.mpNode->mValue.second);
		}
		else
		{
			invalidResearches.push_back(it.mpNode->mValue.second);
		}

	}
	validResearches.insert(validResearches.end(), invalidResearches.begin(), invalidResearches.end());


	for each(ResearchType research in validResearches)
	{
		if (!HasResearched(research.mResearchID))
		{
			bool canShow = false;
			if (research.mPriorResearches.size() != 0)
			{
				for each (ResearchType prior in research.mPriorResearches)
				{
					if (!HasResearched(prior.mResearchID))
					{
						for each (ResearchType prior2 in prior.mPriorResearches)
						{
							if (HasResearched(prior2.mResearchID))
							{
								canShow = true;
							}
						}
						if (prior.mPriorResearches.size() == 0)
						{
							canShow = true;
						}
					}
					else
					{
						canShow = true;
					}
				}
			}
			else
			{
				canShow = true;
			}

			if (canShow)
			{
				UTFWin::UILayout* layout = new UTFWin::UILayout();
				layout->LoadByID(id("ResearchItem"));
				layout->SetParentWindow(inventoryWindow);

				layout->SetVisible(true);


				if (auto itemWindow = layout->FindWindowByID(id("ItemID")))
				{
					auto icon = itemWindow->FindWindowByID(id("ItemIcon"));

					ResourceKey imgKey;
					if (App::Property::GetKey(research.mpPropList.get(), id("ResearchImage"), imgKey))
					{
						ImagePtr img;
						if (Image::GetImage(imgKey, img))
						{
							ImageDrawable* drawable = new ImageDrawable();
							drawable->SetImage(img.get());
							icon->SetDrawable(drawable);
						}
					}

					itemWindow->SetFlag(UTFWin::WindowFlags::kWinFlagAlwaysInFront, true);
					itemWindow->FindWindowByID(id("itembutton"))->AddWinProc(new cResearchButtonWinProc(itemWindow, research));
					itemWindow->SetLayoutLocation((65 * (i % 6)) + (8 * ((i % 6) + 1)), div((i), 6).quot * 75);

					mpItemUIs.push_back(itemWindow);
				}
				i++;
			}
		}
		
	}
}

//Private functions

bool cSSResearchManager::SetupResearches()
{
	vector<uint32_t> researchIDs;
	PropManager.GetPropertyListIDs(id("SS-research"), researchIDs);

	for (int i = 0; i < 5; i++)
	{
		for each (uint32_t resID in researchIDs)
		{
			try
			{
				ResearchType res = ResearchType(resID);
				bool hideResearch;
				if (App::Property::GetBool(res.mpPropList.get(), id("ResearchHide"), hideResearch))
				{
					if (hideResearch != true)
						mResearchTypes.emplace(res.mResearchID,res);
				}
				else
				{
					mResearchTypes.emplace(res.mResearchID, res);
				}
			}
			catch (std::exception except)
			{
				const char* text = except.what();
				wstring report;
				report.assign_convert(text);
				MessageBox(NULL, report.c_str(), LPCWSTR(u"Error adding research"), 0x00000010L);
			}
		}
	}
	return false;
}

cSSResearchManager* cSSResearchManager::sInstance;


//Struct con-struct-or
ResearchType::ResearchType(uint32_t propID)
{
	if (propID == 0)
	{
		mRequiredPoints = 0;
		mResearchID = 0;
		mToolID = 0;
		return;
	}

	if (PropManager.GetPropertyList(propID, id("SS-research"), mpPropList))
	{
		mResearchID = propID;
		App::Property::GetUInt32(mpPropList.get(), id("ResearchTool"), mToolID);

		App::Property::GetText(mpPropList.get(), id("ResearchName"), mResearchTitle);
		App::Property::GetText(mpPropList.get(), id("ResearchDescript"), mResearchDescription);

		size_t count;
		uint32_t* ids;
		App::Property::GetArrayUInt32(mpPropList.get(), id("ResearchDependancies"), count, ids);
		if (count != 0)
		{
			for (int i = 0; i < count; i++)
			{
				mPriorResearches.push_back(ids[i]);
			}
		}

		if (!App::Property::GetUInt32(mpPropList.get(), id("ResearchPointsRequired"), mRequiredPoints))
		{
			string error = "Research property list " + to_string(propID) + " has no required point count!";
			throw std::invalid_argument(error.c_str());
		}
	}
	else
	{
		string error = "Research property list " + to_string(propID) + " is not valid!";
		throw std::invalid_argument(error.c_str());
	}
}

ResearchType::ResearchType()
{
	mRequiredPoints = 0;
	mResearchID = 0;
	mToolID = 0;
}

const bool ResearchType::operator==(const ResearchType other)
{
	return other.mpPropList == mpPropList && other.mPriorResearches == mPriorResearches
		&& other.mRequiredPoints == mRequiredPoints && other.mToolID == mToolID && mResearchID == other.mResearchID;
}

const bool ResearchType::operator!=(const ResearchType other)
{
	return !(other.mpPropList == mpPropList && other.mPriorResearches == mPriorResearches
		&& other.mRequiredPoints == mRequiredPoints && other.mToolID == mToolID && other.mResearchID == mResearchID);
}

ResearchType::operator bool() const
{
	return (mResearchID != 0);
}
