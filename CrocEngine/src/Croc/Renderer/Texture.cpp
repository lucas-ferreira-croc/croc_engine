#include "crocpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLTexture.h"

namespace Croc{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   CROC_CORE_ASSERT(false, "RendererAPI::None is currentyly not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		CROC_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   CROC_CORE_ASSERT(false, "RendererAPI::None is currentyly not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		CROC_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

	
}