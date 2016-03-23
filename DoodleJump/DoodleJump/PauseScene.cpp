#include "stdafx.h"
#include "PauseScene.h"

pauseScene::pauseScene()
{
	backButton = new sf::Sprite;
	backButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	backButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	backButton->setPosition(200, 210);
	backText.setFont(assets->font);
	backText.setCharacterSize(20);
	backText.setString("Back");
	backText.setStyle(sf::Text::Bold);
	backText.setPosition(232.f, 212.f);
	backText.setColor(sf::Color(0, 0, 0));

	exitButton = new sf::Sprite;
	exitButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	exitButton->setPosition(250, 270);
	exitText.setFont(assets->font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(280.f, 272.f);
	exitText.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

pauseScene::~pauseScene()
{
	delete background;
	delete backButton;
	delete exitButton;
	background = NULL;
	backButton = NULL;
	exitButton = NULL;
}

gameResult pauseScene::onPauseMenu(sf::RenderWindow & window) 
{
	backButton->setPosition(view.getCenter().x - 275.f + 200.f, view.getCenter().y - 350.f + 210.f);
	backText.setPosition(view.getCenter().x - 275.f + 232.f, view.getCenter().y - 350.f + 212.f);
	exitButton->setPosition(view.getCenter().x - 275.f + 250.f, view.getCenter().y - 350.f + 270.f);
	exitText.setPosition(view.getCenter().x - 275.f + 280.f, view.getCenter().y - 350.f + 272.f);
	background->setPosition(view.getCenter().x-275.f, view.getCenter().y - 350.f);

	window.clear(sf::Color(255, 255, 255));

	window.draw(*background);
	window.draw(*backButton);
	window.draw(backText);
	window.draw(*exitButton);
	window.draw(exitText);
	window.display();

	gameResult result;
	sf::Event event;
	while (window.pollEvent(event))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
			&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
		{
			backButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			backButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
		}

		if (((mousePosition.y >= 270) && (mousePosition.y <= 299)
			&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
		{
			exitButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
		}

		if (sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
				&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
			{
				result.gameStatus = statusGame::GAME_SCENE;
				return result;
			}
			if (((mousePosition.y >= 270) && (mousePosition.y <= 299)
				&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
			{
				window.close();
			}

		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
	result.gameStatus = statusGame::PAUSE_SCENE;
	return result;
}
