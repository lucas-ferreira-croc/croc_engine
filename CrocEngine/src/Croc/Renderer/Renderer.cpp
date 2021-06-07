#include "crocpch.h"
#include "Renderer.h"


namespace Croc {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjetcionMatrix = camera.GetViewProjectionMatrix();
	}
	
	void Renderer::EndScene()
	{
	
	}
	
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjetcionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}