/*
*	 Copyright (C) 2018 Qub�d Engine Group.
*	 All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification,
*  are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, this
*  list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice,
*  this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. Neither the name of the copyright holder nor the names of its contributors
*  may be used to endorse or promote products derived from this software without
*  specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <qub3d/window.hpp>
#include <qub3d/opengl.hpp>

using namespace qub3d;

Window::Window(const std::string& title, unsigned int w, unsigned int h): m_isRunning(true)
{
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	glewExperimental = GL_TRUE;
	glewInit();

	SDL_ShowWindow(m_window);
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_context);
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::pollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		if (e.type == SDL_QUIT) 
			m_isRunning = false;

		for (const EventHandler& handleEvent : m_eventHandlers)
		{
			handleEvent(e);
		}
	}
}

void Window::addEventHandler(EventHandler handler)
{
	m_eventHandlers.push_back(handler);
}