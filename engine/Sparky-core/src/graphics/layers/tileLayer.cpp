#include "tileLayer.h"

namespace sparky { namespace graphics {

	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, maths::Mat4::otrthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {

		m_Bounds.minX = -10;
		m_Bounds.maxX = 10;
		m_Bounds.minY = -10;
		m_Bounds.maxY = 10;
	}

	TileLayer::~TileLayer() {}


		
	sparky::maths::Vec2 TileLayer::getTilePos(sparky::maths::Vec2 pointer)
	{
		int tileX = (int)(pointer.x / m_TileSize);
		tileX = tileX < 0 ? tileX - 1 : tileX;
		int tileY = (int)(pointer.y / m_TileSize);
		tileY = tileY < 0 ? tileY - 1 : tileY;

		float x = static_cast<float>(tileX) * m_TileSize;
		float y = static_cast<float>(tileY) * m_TileSize;

		return sparky::maths::Vec2(x, y);
	}
}}