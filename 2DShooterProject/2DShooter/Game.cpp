#include "Game.h"

#include <iostream>

#include "SDLSystem.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "MenuButton.h"
#include "Player.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"
#include "BaseCreator.h"

Game::Game(token) :
	m_bRunning(false),
	m_pGameStateMachine(0),
	m_playerLives(3),
	m_scrollSpeed((float)1.8),
	m_bLevelComplete(false),
	m_bChangingState(false)
{
	// add some level files to an array
	m_levelFiles.push_back("assets/map1.tmx");
	m_levelFiles.push_back("assets/map2.tmx");

	// start at this level
	m_currentLevel = 1;
}

bool Game::init()
{
	TheSDLSystem::Instance().init("Chapter 1", 100, 100, 640, 480, false);

	// add some sound effects - TODO move to better place
	TheSoundManager::Instance().load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance().load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance().load("assets/phaser.wav", "shoot", SOUND_SFX);
	
	TheSoundManager::Instance().playMusic("music1", -1);

	//TheInputHandler::Instance().initialiseJoysticks();

	// register the types for the game
	TheGameObjectFactory::Instance().registerType("MenuButton", new ObjCreator<MenuButton>);
	TheGameObjectFactory::Instance().registerType("Player", new ObjCreator<Player>);
	TheGameObjectFactory::Instance().registerType("AnimatedGraphic", new ObjCreator<AnimatedGraphic>);
	TheGameObjectFactory::Instance().registerType("ScrollingBackground", new ObjCreator<ScrollingBackground>);
	TheGameObjectFactory::Instance().registerType("Turret", new ObjCreator<Turret>);
	TheGameObjectFactory::Instance().registerType("RoofTurret", new ObjCreator<RoofTurret>);
	TheGameObjectFactory::Instance().registerType("Glider", new ObjCreator<Glider>);
	TheGameObjectFactory::Instance().registerType("ShotGlider", new ObjCreator<ShotGlider>);
	TheGameObjectFactory::Instance().registerType("Eskeletor", new ObjCreator<Eskeletor>);
	TheGameObjectFactory::Instance().registerType("Level1Boss", new ObjCreator<Level1Boss>);


	// start the menu state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true; //everything inited successfully, start the main loop

	return true;
}

void Game::render()
{
	//clear the renderer to the draw colour
	TheSDLSystem::Instance().clearScreen();

	m_pGameStateMachine->render();

	//draw to the window
	TheSDLSystem::Instance().drawScreen();
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance().update();
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	TheInputHandler::Instance().clean();

	m_pGameStateMachine->clean();

	m_pGameStateMachine = nullptr;
	delete m_pGameStateMachine;

	TheTextureManager::Instance().clearTextureMap();

	TheSDLSystem::Instance().quit();
}

void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	m_pGameStateMachine->reloadState();
	m_bLevelComplete = false;
}
