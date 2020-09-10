#include "PauseState.h"

#include "Game.h"
#include "MainMenuState.h"

#include "InputHandler.h"
#include "SoundManager.h"

const std::string PauseState::s_pauseID = "PAUSE";

bool PauseState::onEnter()
{
	TheInputHandler::Instance().reset();

	GameState::onEnter();

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	GameState::onExit();

	return false;
}

bool PauseState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheSoundManager::Instance().playSound("unPause", 0);
			s_resumePlay();
		}

		return true;
	}
	return false;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance().getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance().getStateMachine()->popState();
}
