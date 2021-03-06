#pragma once

#include "Croc/Core/Core.h"
#include "Croc/Events/Event.h"
#include "Croc/Core/Timestep.h"

namespace Croc {

	class CROC_API Layer 
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}