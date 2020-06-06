#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"
#include "GameObject.h"

class StateParser
{
public:

	StateParser() {}
	~StateParser() {}

	bool parseState(std::string assetsLocation, std::string stateFile, std::string stateID,
					std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
private:
	void parseObjects(TiXmlElement* pObjectRoot, std::vector<GameObject*> *pObjects);
	void parseTextures(std::string assetsLocation,TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs);

};

#endif /* defined ( __StateParser__ ) */