#include <Croc.h>

#include "Plataform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SampleLayer : public Croc::Layer
{
public:
	SampleLayer() :
		Layer("Sample"), m_CameraController(1280.0f / 720.0f)
	{
		// Triangle Vertex Array Stuff

		m_VertexArray.reset(Croc::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.3f, 0.8f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.9f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f
		};

		Croc::Ref<Croc::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Croc::VertexBuffer::Create(vertices, sizeof(vertices)));
		Croc::BufferLayout layout = {
			{ Croc::ShaderDataType::Float3, "a_Position" },
			{ Croc::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Croc::Ref<Croc::IndexBuffer> indexBuffer;
		indexBuffer.reset(Croc::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square Vertex Array Stuff

		m_SquareVA.reset(Croc::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};


		Croc::Ref<Croc::VertexBuffer> squareVB;
		squareVB.reset(Croc::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Croc::ShaderDataType::Float3, "a_Position" },
			{ Croc::ShaderDataType::Float2, "a_TexCoord" }
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Croc::Ref<Croc::IndexBuffer> squareIB;
		squareIB.reset(Croc::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;				

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = Croc::Shader::Create("VertexPosColor", vertexSource, fragmentSource);


		std::string flatColorVertexSource = R"(

			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	

			}
		)";

		std::string flatColorFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = Croc::Shader::Create("FlatColor", flatColorVertexSource, flatColorFragmentSource);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Croc::Texture2D::Create("assets/textures/croc_engine_logo.png");

		std::dynamic_pointer_cast<Croc::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Croc::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Croc::Timestep timestep) override
	{
	
		// Update
		m_CameraController.OnUpdate(timestep);

		// Renderer
		Croc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Croc::RenderCommand::Clear();

		Croc::Renderer::BeginScene(m_CameraController.GetCamera());
		
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Croc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Croc::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}			
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Croc::Renderer::Submit(m_Shader, m_VertexArray);
		Croc::Renderer::Submit(textureShader, m_SquareVA,  glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		
		Croc::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Croc::Event& e) override
	{
		m_CameraController.OnEvent(e);

	}

	bool OnKeyPressedEvent(Croc::KeyPressedEvent& event)
	{
		
	}

private:

	Croc::ShaderLibrary m_ShaderLibrary;

	Croc::Ref<Croc::Shader> m_Shader;
	Croc::Ref<Croc::VertexArray> m_VertexArray;

	Croc::Ref<Croc::Shader> m_FlatColorShader;
	Croc::Ref<Croc::VertexArray> m_SquareVA;;

	Croc::Ref<Croc::Texture2D> m_Texture;

	Croc::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Croc::Application
{
public:
	Sandbox() 
	{		
		PushLayer(new SampleLayer());
	}

	~Sandbox() 
	{
	}
};

Croc::Application* Croc::CreateApplication() 
{
	return new Sandbox();
}