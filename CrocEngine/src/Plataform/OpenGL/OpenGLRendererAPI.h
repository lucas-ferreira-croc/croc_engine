#pragma once

#include "Croc/Renderer/RendererAPI.h"

namespace Croc {
	
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}
