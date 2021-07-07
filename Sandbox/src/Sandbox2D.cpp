#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Plataform/OpenGL/OpenGLShader.h"

#include <chrono>

template<typename Fn>
class Timer 
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		
		float duration = (end - start) * 0.001f;
		m_Stopped = true;
		std::cout << m_Name << " Duration: " << duration << " ms" << std::endl;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })
Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Croc::Texture2D::Create("assets/textures/croc_engine_logo.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Croc::Timestep timestep)
{
	PROFILE_SCOPE("Sanbox2D::OnUpdate");
	// Update
	
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	// Renderer
	{
		PROFILE_SCOPE("Pre Renderer");
		Croc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Croc::RenderCommand::Clear();
	}
	
	{
		PROFILE_SCOPE("Renderer Draw");
		Croc::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Croc::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f,  0.80f }, { 77.0f / 255.0f , 28.0f / 255.0f, 184.0f / 255.0f  , 1.0f });
		Croc::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f,  0.70f }, { 0.3f, 0.3f, 1.0f, 1.0f });
		Croc::Renderer2D::DrawQuad({  0.0f,  0.0f }, { 0.5f,  0.50f }, m_Texture);
		Croc::Renderer2D::EndScene();
	}
	//std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	//Croc::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

	for (auto& result : m_ProfileResults) 
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
}

void Sandbox2D::OnEvent(Croc::Event& e)
{
	m_CameraController.OnEvent(e);
}
