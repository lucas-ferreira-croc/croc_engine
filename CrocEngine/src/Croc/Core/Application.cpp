#include "crocpch.h"
#include "Application.h"

#include "Croc/Core/Log.h"

#include "Croc/Renderer/Renderer.h"

#include "Input.h"

#include <glfw/glfw3.h>

namespace Croc 
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		CROC_PROFILE_FUNCTION();

		CROC_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		CROC_PROFILE_FUNCTION();
		
	}

	void Application::PushLayer(Layer* layer)
	{
		CROC_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		CROC_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		CROC_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
					break;
		}
	}

	void Application::Run() 
	{
		CROC_PROFILE_FUNCTION();
		while (m_Running) 
		{
			CROC_PROFILE_SCOPE("Run Loop");

			float time = (float)glfwGetTime(); // Plataform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			if( !m_Minemized )
			{ 
				{	CROC_PROFILE_SCOPE("Layer OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			{
				CROC_PROFILE_SCOPE("Layer OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		CROC_PROFILE_FUNCTION();

		if(e.GetWidth() == 0 || e.GetHeight() == 0  )
		{
			m_Minemized = true;
			return false;
		}

		m_Minemized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
