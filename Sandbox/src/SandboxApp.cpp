#include <Croc.h>

class Sandbox : public Croc::Application
{
public:
	Sandbox() 
	{
	}

	~Sandbox() 
	{
	}
};

Croc::Application* Croc::CreateApplication() 
{
	return new Sandbox();
}