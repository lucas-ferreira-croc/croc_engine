#pragma once

#ifdef CROC_PLATAFORM_WINDOWS

extern Croc::Application* Croc::CreateApplication();

int main(int argc, char** argv)
{

	Croc::Log::Init();

	CROC_PROFILE_BEGIN_SESSION("Startupt", "CrocProfile-Startup.json");
	auto app = Croc::CreateApplication();
	CROC_PROFILE_END_SESSION();

	CROC_PROFILE_BEGIN_SESSION("Runtime", "CrocProfile-Runtime.json");
	app->Run();
	CROC_PROFILE_END_SESSION();

	CROC_PROFILE_BEGIN_SESSION("ShutDown", "CrocProfile-ShutDown.json");
	delete app;
	CROC_PROFILE_END_SESSION();
}
	
#endif