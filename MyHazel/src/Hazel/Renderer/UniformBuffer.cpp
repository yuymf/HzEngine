#include "hzpch.h"
#include "Hazel/Renderer/UniformBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"


namespace Hazel {


	Ref<Hazel::UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLUniformBuffer>(size, binding);
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
