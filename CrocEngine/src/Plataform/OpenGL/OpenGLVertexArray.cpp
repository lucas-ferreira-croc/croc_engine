#include "crocpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Croc {
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Croc::ShaderDataType::Float:   return GL_FLOAT;
			case Croc::ShaderDataType::Float2:  return GL_FLOAT;
			case Croc::ShaderDataType::Float3:  return GL_FLOAT;
			case Croc::ShaderDataType::Float4:  return GL_FLOAT;
			case Croc::ShaderDataType::Mat3:    return GL_FLOAT;
			case Croc::ShaderDataType::Mat4:	return GL_FLOAT;
			case Croc::ShaderDataType::Int:		return GL_INT;
			case Croc::ShaderDataType::Int2:	return GL_INT;
			case Croc::ShaderDataType::Int3:	return GL_INT;
			case Croc::ShaderDataType::Int4:	return GL_INT;
			case Croc::ShaderDataType::Bool:	return GL_BOOL;
		}

		CROC_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		CROC_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		CROC_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	void OpenGLVertexArray::Bind() const
	{
		CROC_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		CROC_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CROC_PROFILE_FUNCTION();
		CROC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),  "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}