/*
 * Copyright (C) Victor Nivet
 * 
 * This file is part of Nugem.
 * 
 * Nugem is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 * Nugem is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 *  along with Nugem.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "game.h"
#include "character.h"

#include "scenemenu.h"

#include <iostream>
#include <dirent.h>

#include <dirent.h>

Game::Game(): m_currentScene(nullptr)
{
	// SDL initialization
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
	// Initialize window
	m_winWidth = DEFAULT_WINDOW_WIDTH;
	m_winHeight = DEFAULT_WINDOW_HEIGHT;
	m_window = SDL_CreateWindow("NUGEM",
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          m_winWidth, m_winHeight,
	                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
	glGraphics.initialize(m_window);
}

Game::~Game()
{
	if (m_currentScene)
		delete m_currentScene;
	// SDL deinitialization
	glGraphics.finish();
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		m_inputManager.processSDLEvent(e);
	}
	glGraphics.clear();
	//Place your simulation code and rendering code here
	if (m_currentScene)
		m_currentScene->render(glGraphics);
}

void Game::run()
{
	m_currentScene = new SceneMenu();
	glGraphics.clear();
	// 60 fps
	uint32_t tickdelay = 1000 / 60;
	// Main game loop
	while (!SDL_QuitRequested()) {
		uint32_t tick = SDL_GetTicks();
		update();
		uint32_t dt = SDL_GetTicks() - tick;
		if (dt < tickdelay)
			SDL_Delay(tickdelay - dt);
	}
}

