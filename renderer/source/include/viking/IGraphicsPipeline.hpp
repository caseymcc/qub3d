#pragma once

#include <viking/VertexBufferBase.hpp>
#include <viking/ShaderStage.hpp>
#include <viking/IModelPool.hpp>
#include <map>

namespace viking
{
	class IGraphicsPipeline
	{
	public:
		IGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths);

		virtual void attachModelPool(IModelPool* pool) = 0;
		virtual void build() = 0;
		virtual void attachVertexBinding(VertexBufferBase vertex) = 0;
	protected:
		std::map<ShaderStage, const char*> m_shader_paths;
	};
}