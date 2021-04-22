#pragma once

#ifdef CROC_PLATAFORM_WINDOWS

extern Croc::Application* Croc::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Croc::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
	
#endif