#pragma once

#include <string>
#include "layer.h"
#include "../renderer/batchRenderer2d.h"
#include "../../maths/vec2_int.h"
#include "../renderable/bounds.h"
#include "../../maths/mat4.h"

namespace my_app_engine { namespace graphics {
	class TileLayer : public Layer
	{
	private:
		float m_TileSize = 0.5;
		my_app_engine::graphics::Bounds m_Bounds;
	public:
		TileLayer(std::string id, my_app_engine::maths::Mat4, my_app_engine::graphics::Shader* shader, my_app_engine::graphics::Renderer2D* renderer);
		virtual ~TileLayer();

		my_app_engine::maths::Vec2 getTilePos(my_app_engine::maths::Vec2 pointer);
	
		inline float getTileSize() const
		{
			return m_TileSize;
		}
	};
}}