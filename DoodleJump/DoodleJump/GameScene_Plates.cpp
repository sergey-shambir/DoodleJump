#include "stdafx.h"
#include "sheet.h"

int GameScene::getUppermostPlateID() const
{
	std::vector<float> platePosition;
	platePosition.reserve(NUMBER_PLATES);
	for (auto &plate : m_plates)
	{
		platePosition.push_back(plate->getPosition().y);
	}
	return std::distance(platePosition.begin(), std::min_element(platePosition.begin(), platePosition.end()));
}

sf::Vector2f GameScene::getCenterPlatePosition(int plateID) const
{
	float x = m_plates[plateID]->getPosition().x + PLATE_WIDTH / 2;
	float y = m_plates[plateID]->getPosition().y + PLATE_HEIGHT / 2;

	return sf::Vector2f(x, y);
}

void GameScene::buildPlate(int startingPointPlateID, int plateIndex)
{
	sf::Vector2f startingPoint = getCenterPlatePosition(startingPointPlateID);
	float offsetY = float((rand() % 100) + PLATE_HEIGHT + DOODLE_HEIGHT);
	float offsetX = (sqrt(242 * 242 - offsetY * offsetY));
	if (rand() % 2)
	{
		offsetX *= -1;
	}
	float x = float(int(startingPoint.x + offsetX + WINDOW_WIDTH - PLATE_WIDTH) % (WINDOW_WIDTH - PLATE_WIDTH));
	float y = startingPoint.y - offsetY;
	
	int divider = 3 + rand() % (1 + plateIndex % 2); // NOTE: interesting engineering solution
	switch (rand() % divider)
	{
	case 0:
		m_plates[plateIndex]->setType(PlateType::STATIC);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_STATIC_TEXTURE);
		m_plates[plateIndex]->setSpeedX(0);
		break;
	case 1:
		m_plates[plateIndex]->setType(PlateType::STATIC_DYNAMIC_X);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_DYNAMIC_TEXTURE);

		m_plates[plateIndex]->setSpeedX((rand() % 3) + 1);
		if (rand() % 2)
		{
			m_plates[plateIndex]->setSpeedX(-m_plates[plateIndex]->getSpeedX());
		}
		break;
	case 2:
		m_plates[plateIndex]->setType(PlateType::CLOUD);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_CLOUD_TEXTURE);
		m_plates[plateIndex]->setSpeedX(0);
		break;
	case 3:
		m_plates[plateIndex]->setType(PlateType::UNSTABLE);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_UNSTABLE_TEXTURE);

		m_plates[plateIndex]->setSpeedX(rand() % 3);
		if (rand() % 2)
		{
			m_plates[plateIndex]->setSpeedX(-m_plates[plateIndex]->getSpeedX());
		}
		break;
	default:
		assert(0);
		break;
	}
	m_plates[plateIndex]->setRotation(0);
	m_plates[plateIndex]->setPosition(sf::Vector2f(x, y));
}

void GameScene::generPlates()
{
	float viewPositionY = m_view.getCenter().y;	
	for (int i = 0; i < NUMBER_PLATES; ++(++i))
	{
		if ((m_plates[i]->getPosition().y > viewPositionY + WINDOW_HEIGHT / 2) && (m_plates[i + 1]->getPosition().y > viewPositionY + WINDOW_HEIGHT / 2))
		{
			int uppermostPlateID = getUppermostPlateID();
			buildPlate(uppermostPlateID, i);
			buildPlate(uppermostPlateID, i + 1);
		}
	}
}

void GameScene::dropUnstablePlates()
{
	for (auto &plate : m_plates)
	{
		if (plate->getFallStatus() == true)
		{
			plate->rotate(-1.f);
			plate->move(sf::Vector2f(-STEP, 4 * STEP));
			if (plate->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
			{
				plate->setRotation(0);
				plate->setFallStatus(false);
			}
		}
	}
}

void GameScene::moveDynamicPlates()
{
	for (auto &plate : m_plates)
	{
		sf::Vector2f platePosition = plate->getPosition();
		int speedX = plate->getSpeedX();
		if (speedX < 0)
		{
			if (platePosition.x <= 0)
			{
				plate->setSpeedX(-speedX);
			}
		}
		if (speedX > 0)
		{
			if (platePosition.x >= WINDOW_WIDTH - PLATE_WIDTH)
			{
				plate->setSpeedX(-speedX);
			}
		}
		plate->move(sf::Vector2f(float(speedX), 0));
	}
}
