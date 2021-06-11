#include "crocpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLShader.h"

namespace Croc {
	
	
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   CROC_CORE_ASSERT(false, "RendererAPI::None is currentyly not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		CROC_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}


	Ref<Shader> Shader::Create(const std::string& name , const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   CROC_CORE_ASSERT(false, "RendererAPI::None is currentyly not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		CROC_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

	void ShaderLibrary::Add(const std::string name, const Ref<Shader>& shader)
	{
		CROC_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CROC_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}