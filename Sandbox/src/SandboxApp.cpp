#include <Croc.h>

#include <imgui/imgui.h>

class SampleLayer : public Croc::Layer 
{
public:
	SampleLayer()
		: Layer("Sample") 
	{
		CROC_INFO("Sample Layer Created Succesfully");
	}

	virtual void OnUpdate() override
	{
		//CROC_INFO("SampleLayer::Update");
		
		if (Croc::Input::isKeyPressed(CROC_KEY_SPACE))
			CROC_TRACE("Space key is pressed (pool)!");
	}

	virtual void OnImGuiRender() override
 	{
		ImGui::Begin("Teste");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	virtual void OnEvent(Croc::Event& event) override
	{
		//CROC_TRACE("{0}", event);

		if (event.GetEventType() == Croc::EventType::KeyPressed)
		{
			Croc::KeyPressedEvent& e = (Croc::KeyPressedEvent&)event;
			CROC_TRACE("{0}", (char)e.GetKeyCode());

			if (Croc::Input::isKeyPressed(CROC_KEY_SPACE))
				CROC_TRACE("Space key is pressed (event)!");

		}
	}
};

class Sandbox : public Croc::Application
{
public:
	Sandbox() 
	{
		PushLayer(new SampleLayer);
	}

	~Sandbox() 
	{
	}
};

Croc::Application* Croc::CreateApplication() 
{
	return new Sandbox();
}