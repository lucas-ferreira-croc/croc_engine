#include <Croc.h>

class SampleLayer : public Croc::Layer 
{
public:
	SampleLayer()
		: Layer("Sample") 
	{
		CROC_INFO("Sample Layer Created Succesfully");
	}

	void OnUpdate() override
	{
		CROC_INFO("SampleLayer::Update");
	}

	void OnEvent(Croc::Event& event) override
	{
		CROC_TRACE("{0}", event);
	}
};

class Sandbox : public Croc::Application
{
public:
	Sandbox() 
	{
		PushLayer(new SampleLayer());
	}

	~Sandbox() 
	{
	}
};

Croc::Application* Croc::CreateApplication() 
{
	return new Sandbox();
}