#include "StateParser.h"

#include "SDLSystem.h"
#include "ParserManager.h"
#include "SoundManager.h"


bool StateParser::parseState(GameState* pState)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	//get the root element
	TiXmlElement* pRoot = loadDocument(xmlDoc, TheParserManager::Instance().m_rootPath, m_stateFile);

	//get this states root node and assign it to pStateRoot
	TiXmlElement* pStateRoot = nullptr;
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == pState->getStateID())
		{
			pStateRoot = e;
			break;
		}
	}

	//get pStageElem and pAudioElem from the root node
	TiXmlElement* pStageElem = nullptr;
	TiXmlElement * pAudioElem = nullptr;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("STAGE"))
		{
			pStageElem = e;
		}
		else if (e->Value() == std::string("SOUND"))
		{
			pAudioElem = e;
		}
		else
		{
			std::cout << "no TiXmlElement* for " << e->Value() << " in StateParser::parseState \n";
			if (pStageElem && pAudioElem)
			{
				break;
			}
		}
	}

	//parse a subpath if present 
	//std::string path = TheParserManager::Instance().m_rootPath;
	std::string subpath = "";
	if (pStageElem->FirstChildElement()->Attribute("subpath"))
	{
		subpath += pStageElem->FirstChildElement()->Attribute("subpath");
	}

	subpath += pStageElem->FirstChildElement()->Attribute("filename");
	//pState->stageAssetsPath() = path;
	//pState->stageMapFileName() = pStageElem->FirstChildElement()->Attribute("filename");

	TheParserManager::Instance().m_levelParser.setLevelFile(subpath);

	parseAudio(pAudioElem);

	return true;
}

void StateParser::parseAudio(TiXmlElement* pAudioElem)
{
	for (TiXmlElement* e = pAudioElem->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string filename = TheParserManager::Instance().m_rootPath + TheParserManager::Instance().m_audioFolder;
		if (e->Attribute("subpath"))
		{
			filename += e->Attribute("subpath");
		}
		filename += e->Attribute("filename");

		if (e->Value() == std::string("music"))
		{
			TheSoundManager::Instance().load(filename, e->Attribute("musicID"), SOUND_MUSIC);
		}
		else if (e->Value() == std::string("sfx"))
		{
			TheSoundManager::Instance().load(filename, e->Attribute("sfxID"), SOUND_SFX);
		}
		else
		{
			std::cout << "invalid value: " << e->Value() << " in STATES XML file \n";
		}
	}
}

