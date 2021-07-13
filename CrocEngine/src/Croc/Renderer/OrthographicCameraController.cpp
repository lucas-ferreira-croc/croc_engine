#include "crocpch.h"
#include "OrthographicCameraController.h"


#include "Croc/Core/Input.h"
#include "Croc/Core/KeyCodes.h"

namespace Croc {
		
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			m_Rotation(rotation)
	{
	
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		CROC_PROFILE_FUNCTION();

		float time = ts;

		if (Input::IsKeyPressed(CROC_KEY_A))
			m_CameraPos.x -= m_CameraTranslationSpeed * time;
		else if (Input::IsKeyPressed(CROC_KEY_D))
			m_CameraPos.x += m_CameraTranslationSpeed * time;

		if (Input::IsKeyPressed(CROC_KEY_S))
			m_CameraPos.y -= m_CameraTranslationSpeed * time;
		else if (Input::IsKeyPressed(CROC_KEY_W))
			m_CameraPos.y += m_CameraTranslationSpeed * time;

		if(m_Rotation)
		{
			if (Input::IsKeyPressed(CROC_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * time;
			if (Input::IsKeyPressed(CROC_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * time;
		
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPos);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		CROC_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CROC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CROC_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		CROC_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
	
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		CROC_PROFILE_FUNCTION();

		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}