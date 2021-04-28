#include "Application.h"

#include "Croc/Events/ApplicationEvent.h"
#include "Croc/Log.h"
#include <iostream>


namespace Croc 
{

	Application::Application()
	{

	}

	Application::~Application()
	{
	}


	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		
		CROC_TRACE(e);
	
		while (true);
	}
}
