#include "crocpch.h"
#include "Application.h"

#include "Croc/Events/ApplicationEvent.h"
#include "Croc/Log.h"

#include <GLFW/glfw3.h>

namespace Croc 
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}


	void Application::Run() 
	{
		while (m_Running) 
		{
			glClearColor(77.0f / 255.0f, 28.0f / 255.0f, 184.0f / 255.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
