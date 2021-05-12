#pragma once

#ifdef CROC_PLATAFORM_WINDOWS

extern Croc::Application* Croc::CreateApplication();

int main(int argc, char** argv)
{

	Croc::Log::Init();
	CROC_CORE_WARN("Core Log System Inicialized!");
	CROC_INFO("Client Log System Initialized!");

	auto app = Croc::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
	
#endif