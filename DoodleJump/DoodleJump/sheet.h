#pragma once

#include "stdafx.h"

#if defined(_WIN64) 
    #pragma comment(lib, "winmm.lib")
#elif defined(_WIN32) 
	#pragma comment(lib, "winmm.lib")
#else 
	#error "Unknown platform" 
#endif

//#pragma comment(lib,"Winmm.lib")
#include <algorithm>
#include <array>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include "bases.h"
#include "assets.h"
#include "bonus.h"
#include "plate.h"	
#include "doodle.h"
#include "pauseScene.h"
#include "gameFrame.h"
#include "gameOverScene.h"
#include "helpScene.h"
#include "startScene.h"
#include "game.h"

extern Assets * assets; // TODO: ���������������� ������� ��������� ��������
extern sf::View view; // TODO: ���������������� ������� ��������� ��������