#include <Croc.h>

#include "imgui/imgui.h"

class SampleLayer : public Croc::Layer
{
public:
	SampleLayer() :
		Layer("Sample")
	{

	}

	void OnUpdate() override
	{
		if (Croc::Input::isKeyPressed(CROC_KEY_SPACE))
			CROC_TRACE("Space Key is Pressed(poll!)");
	}

	virtual void OnImGuiRender() override
	{
		
		
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Croc::Event& event) override
	{
		if(event.GetEventType() == Croc::EventType::KeyPressed)
		{
			Croc::KeyPressedEvent& e = (Croc::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CROC_KEY_SPACE)
				CROC_TRACE("Space Key is pressed(event)!");
			CROC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Croc::Application
{
public:
	Sandbox() 
	{		
		//PushLayer(new SampleLayer());
	}

	~Sandbox() 
	{
	}
};

Croc::Application* Croc::CreateApplication() 
{
	return new Sandbox();
}