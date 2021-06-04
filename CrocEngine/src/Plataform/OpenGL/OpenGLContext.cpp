#include "crocpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Croc {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)

	{
		CROC_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CROC_CORE_ASSERT(status, "Failed to initialize Glad!");

		CROC_CORE_INFO("OpenGL Info:");
		CROC_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CROC_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CROC_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}