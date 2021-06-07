#include "crocpch.h"
#include "RenderCommand.h"

#include "plataform/OpenGL/OpenGLRendererAPI.h"

namespace Croc {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}