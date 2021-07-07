#pragma once

#include "Croc/Core/Layer.h"

#include "Croc/Events/MouseEvent.h"
#include "Croc/Events/KeyEvent.h"
#include "Croc/Events/ApplicationEvent.h"


namespace Croc {

	class CROC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}