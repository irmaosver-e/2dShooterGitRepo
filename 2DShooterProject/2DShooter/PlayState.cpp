#include "PlayState.h"

#include <iostream>
#include "SDLSystem.h"
#include "Game.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "LevelParser.h"
#include "Level.h"

#include "TextureManager.h"


const std::string PlayState::s_playID = "PLAY";

bool PlayState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance().getStateMachine()->pushState(new PauseState());
		}

		TheBulletHandler::Instance().updateBullets();

		if (TheGame::Instance().getPlayerLives() == 0)
		{
			TheGame::Instance().getStateMachine()->changeState(new GameOverState());
		}

		return true;
	}

	return false;
}

bool PlayState::render()
{
	if (GameState::render())
	{
		for (int i = 0; i < TheGame::Instance().getPlayerLives(); i++)
		{
			TheTextureManager::Instance().drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheSDLSystem::Instance().getRenderer(), 0.0, 255);
		}

		TheBulletHandler::Instance().drawBullets();

		return true;
	}

	return false;
}

bool PlayState::onEnter()
{
	std::cout << "PlayState::onEnter()   setPlayerLives(3) hardcoded";
	TheGame::Instance().setPlayerLives(3);

	GameState::onEnter();

	TheTextureManager::Instance().load("assets/bullet1.png", "bullet1", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/bullet2.png", "bullet2", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/bullet3.png", "bullet3", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/lives.png", "lives", TheSDLSystem::Instance().getRenderer());

	if (m_pLevel)
	{
		m_loadingComplete = true;
	}

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	GameState::onExit();

	TheBulletHandler::Instance().clearBullets();

	return true;
}