#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Plataform/OpenGL/OpenGLShader.h"


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Croc::Timestep timestep)
{
	// Update
	m_CameraController.OnUpdate(timestep);

	// Renderer
	Croc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Croc::RenderCommand::Clear();

	Croc::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Croc::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0, 1.0f }, { 77.0f / 255.0f , 28.0f / 255.0f, 184.0f / 255.0f  , 1.0f });
	Croc::Renderer2D::EndScene();
	
	//std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	//Croc::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Croc::Event& e)
{
	m_CameraController.OnEvent(e);
}
