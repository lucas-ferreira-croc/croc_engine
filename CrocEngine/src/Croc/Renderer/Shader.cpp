#include "crocpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLShader.h"

namespace Croc {
	
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   CROC_CORE_ASSERT(false, "RendererAPI::None is currentyly not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}

		CROC_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}