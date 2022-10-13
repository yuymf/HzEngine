#include "hzpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHanldle)
		: m_windowHandle(windowHanldle)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("Vendor  : {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("Version : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}