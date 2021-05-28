#pragma once

#include "Core.h"

#include "Window.h"
#include "Croc/LayerStack.h"
#include "Croc/Events/Event.h"
#include "Croc/Events/ApplicationEvent.h"

#include "Croc/ImGui/ImGuiLayer.h"

namespace Croc {
	class CROC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

