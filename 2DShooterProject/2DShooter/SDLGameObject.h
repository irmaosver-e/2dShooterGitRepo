#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include <iostream>

class SDLGameObject : public GameObject
{
public:
	virtual ~SDLGameObject() {}

	virtual void load(const LoaderParams& rParams);
	virtual void reset(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void outOfView();
	virtual void inView();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class
	virtual void collisionPassive() {} //not implemented in this class
	virtual void collisionWithLayer() {} //not implemented in this class

	virtual void addAnimation(std::string& animationID) { m_animations.push_back(animationID); }


	virtual std::string objType() { return "SDLGameObject"; }

protected:
	SDLGameObject();

	void refreshTextureVariables();

	//returns true when finished
	bool playAnimation(int animationID, bool playReverse = false);

	//returns true when finished
	bool playTransitionTexture(int animationID);

	//returns true when is new animation and resets the frametimer
	bool switchAnimation(int animationID);

	//returns true when ready to move a frame
	//bool moveAnimFrame();
	
	void trackFrameTime();

	virtual void handleAnimation();
	virtual void handleDying();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;

	std::vector<std::string> m_animations;
};

#endif /* defined( __SDLGameObject__ ) */