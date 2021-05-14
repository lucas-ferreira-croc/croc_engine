#pragma once

#include "Croc/Layer.h"

namespace Croc {

	class CROC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	
	private:
		float m_Time = 0.0f;
	};

}