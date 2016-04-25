#include "stdafx.h"
#include "sheet.h"

Game::Game()
	:m_assets(new Assets())
	,m_view(new sf::View())
{
	m_sceneStart = std::make_unique<StartScene>(*m_assets, *m_view);
	m_sceneHelp = std::make_unique<HelpScene>(*m_assets, *m_view);
	m_scenePause = std::make_unique<PauseScene>(*m_assets, *m_view);
	m_sceneGame = std::make_shared<GameScene>(*m_assets, *m_view);

	std::function<uint64_t()> getter = std::bind(&GameScene::getScore, m_sceneGame);
	m_sceneGameOver = std::make_unique<GameOverScene>(*m_assets, *m_view, getter);
}

Game::~Game()
{

}

void Game::gameLoop(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		switch (m_gameState.status)
		{
		case GameStatus::START_SCENE:
			m_gameState = m_sceneStart->onStartMenu(window);
			break;
		case GameStatus::GAME_SCENE:
			m_gameState = m_sceneGame->onGameFrame(window);
			break;
		case GameStatus::GAME_OVER_SCENE:
			m_gameState = m_sceneGameOver->onGameOverMenu(window);
			break;
		case GameStatus::PAUSE_SCENE:
			m_gameState = m_scenePause->onPauseMenu(window);
			break;
		case GameStatus::HELP_SCENE:
			m_gameState = m_sceneHelp->onHelpMenu(window);
			break;
		}
	}
}

void Game::launch(void)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump", sf::Style::Close, settings);
	sf::Image icon = m_assets->WINDOW_ICON;;
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	m_view->reset(sf::FloatRect(0, 0, 550, 700));
	m_view->setCenter(275, 350);
	window.setView(*m_view);
	m_gameState.status = GameStatus::START_SCENE;

	gameLoop(window);
}
