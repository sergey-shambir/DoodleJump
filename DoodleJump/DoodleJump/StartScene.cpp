#include "stdafx.h"
#include "sheet.h"

StartScene::StartScene(Assets & assets, sf::View & view, SoundHandler & soundHandler)
	:m_assets(assets)
	,m_view(view)
	,m_soundHandler(soundHandler)
{
	m_hero = std::make_unique<Doodle>(m_assets);
	m_plate = std::make_unique<Plate>();
	m_hero->setSpeedY(-20.f);
	m_hero->setTexture(m_assets.DOODLE_RIGHT_TEXTURE);
	m_hero->setPosition(sf::Vector2f(110.f, 500.f - DOODLE_HEIGHT));

	m_title = std::make_unique<sf::Sprite>();
	m_title->setTexture(m_assets.MAIN_TITLE_TEXTURE);
	m_title->setPosition(100.f, 50.f);
	
	m_playButton = std::make_unique<Button>("Play", sf::Vector2f(232.f, 182.f), m_assets);
	m_exitButton = std::make_unique<Button>("Exit", sf::Vector2f(250.f, 240.f), m_assets);
	m_helpButton = std::make_unique<Button>("Help", sf::Vector2f(350.f, 475.f), m_assets);

	m_hole = std::make_unique<sf::Sprite>();
	m_hole->setTexture(m_assets.HOLE_TEXTURE);
	m_hole->setPosition(300.f, 350.f);
	m_hole->setScale(sf::Vector2f(1.25f, 1.25f));

	for (auto &insect : m_insects)
	{
		insect = std::make_unique<sf::Sprite>();
	}

	m_insects[0]->setTexture(m_assets.GARBAGE_1_TEXTURE);
	m_insects[0]->setPosition(450.f, 250.f);
	m_insects[1]->setTexture(m_assets.GARBAGE_2_TEXTURE);
	m_insects[1]->setPosition(300.f, 300.f);
	m_insects[2]->setTexture(m_assets.GARBAGE_3_TEXTURE);
	m_insects[2]->setPosition(210.f, 215.f);
	m_insects[3]->setTexture(m_assets.GARBAGE_4_TEXTURE);
	m_insects[3]->setPosition(50.f, 50.f);
	m_insects[4]->setTexture(m_assets.GARBAGE_5_TEXTURE);
	m_insects[4]->setPosition(400.f, 400.f);

	m_background = std::make_unique<sf::Sprite>();
	m_background->setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_background->setTexture(m_assets.BACKGROUND_TEXTURE);
	m_background->setPosition(0.f, 0.f);

	m_plate->setType(PlateType::STATIC);
	m_plate->setTexture(m_assets.PLATE_STATIC_TEXTURE);
	m_plate->setPosition(sf::Vector2f(100.f, 500.f));
}

StartScene::~StartScene()
{

}

SGameResult StartScene::onStartMenu(sf::RenderWindow & window)
{
	clearResult();

	moveDoodle();
	checkEvents(window);
	render(window);
	window.display();
	return result;
}

void StartScene::clearResult()
{
	result.status = GameStatus::START_SCENE;
}

void StartScene::render(sf::RenderWindow & window) const
{
	window.clear();
	window.draw(*m_background);
	window.draw(*m_title);
	m_plate->draw(window);
	m_hero->draw(window);
	m_playButton->draw(window);
	m_exitButton->draw(window);
	m_helpButton->draw(window);
	window.draw(*m_hole);
	for (auto &insect : m_insects)
	{
		window.draw(*insect);
	}
}

void StartScene::checkMouseOnButtons(sf::Vector2i mousePosition)
{
	m_playButton->onMouse(mousePosition);
	m_exitButton->onMouse(mousePosition);
	m_helpButton->onMouse(mousePosition);
}

void StartScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (m_playButton->onClick(event))
	{
		result.status = GameStatus::GAME_SCENE;
	}
	if (m_exitButton->onClick(event))
	{
		window.close();
	}
	if (m_helpButton->onClick(event))
	{
		result.status = GameStatus::HELP_SCENE;
	}
}

void StartScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkMouseOnButtons(sf::Mouse::getPosition(window));
		checkMouseClick(window, event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void StartScene::moveDoodle()
{
	sf::Vector2f position(0, 0);
	if (m_hero->getSpeedY() < 0)
	{
		m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION);
		position.y = m_hero->getSpeedY();

		m_hero->setTexture(m_assets.DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else
	{
		if (checkCollisionPlates() == Collision::NO_COLLISION)
		{
			m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION / 8);
			position.y = m_hero->getSpeedY();

			m_hero->setTexture(m_assets.DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			m_hero->setSpeedY(-PLATE_DELTA_HEIGHT);
		}
	}
	m_hero->move(position);
}

Collision StartScene::checkCollisionPlates() const
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	sf::Vector2f platePosition = m_plate->getPosition();

	if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition.y + PLATE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= platePosition.x) && (doodlePosition.x - PLATE_WIDTH <= platePosition.x)))
	{
		m_soundHandler.playSound(m_assets.JUMP_SOUND);
		return  Collision::COLLISION_PLATE;
	}
	return Collision::NO_COLLISION;
}
