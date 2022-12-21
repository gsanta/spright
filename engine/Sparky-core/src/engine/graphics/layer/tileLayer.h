#pragma once

#include <string>
#include "layer.h"
#include "../renderer/batchRenderer2d.h"
#include "../renderable/sprite.h"
#include "../../maths/vec2_int.h"
#include "../../../maths/vec2.h"
#include "../renderable/bounds.h"
#include "../renderable/bounds_int.h"
#include "../../../maths/mat4.h"
#include "../camera/camera.h"
#include "dimensions.h"

namespace engine { namespace graphics {
	using namespace spright::maths;

	class TileLayer : public Layer
	{
	private:
		float m_TileSize = 0.5;
		int m_IndexSize;
		Renderable2D** m_TileIndexes;
		BoundsInt m_TileBounds;

	public:
		TileLayer(std::string name, std::string id, engine::graphics::Shader* shader, engine::graphics::Renderer2D* renderer, Camera* camera, Dimensions dimensions);
		virtual ~TileLayer();

		// TODO: find a better name
		Vec2 getBottomLeftPos(Vec2 pointer);
		Vec2 getBottomLeftPos(int tileIndex);
		maths::Vec2Int getTilePos(Vec2 pos);
		Vec2 getWorldPos(int x, int y);

		virtual nlohmann::json getJson() override;
		virtual void setJson(std::string json);
		virtual void add(Sprite* sprite);
		void updateTileIndex(int oldIndex, int newIndex);
		Renderable2D* getAtTileIndex(int tileIndex);
		int getTileIndex(int tileX, int tileY);
		int getTileIndex(Vec2 worldPos);
		const BoundsInt& getTileBounds() const;

		inline float getTileSize() const
		{
			return m_TileSize;
		}
	};
}}
