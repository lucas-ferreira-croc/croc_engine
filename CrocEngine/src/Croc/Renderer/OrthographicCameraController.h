#pragma once

#include "Croc/Renderer/OrthographicCamera.h"
#include "Croc/Core/Timestep.h"

#include "Croc/Events/ApplicationEvent.h"
#include "Croc/Events/MouseEvent.h"

namespace Croc{

	class OrthographicCameraController 
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetCameraTranslationSpeed() const { return m_CameraTranslationSpeed; }
		float GetCameraRotationSpeed() const { return m_CameraRotationSpeed; }

		void SetCameraTranslationSpeed(float speed) { m_CameraTranslationSpeed = speed; }
		void SetCameraRotationSpeed(float speed) { m_CameraRotationSpeed = speed; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPos = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

	};

}