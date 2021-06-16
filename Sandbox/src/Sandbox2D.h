#pragma once

#include "Croc.h"

class Sandbox2D : public Croc::Layer
{
public:
	
	Sandbox2D();
	~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Croc::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Croc::Event& e) override;

private:
	
	//Temporary
	Croc::OrthographicCameraController m_CameraController;

	Croc::Ref<Croc::VertexArray> m_SquareVA;
	Croc::Ref<Croc::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f , 1.0f};
};