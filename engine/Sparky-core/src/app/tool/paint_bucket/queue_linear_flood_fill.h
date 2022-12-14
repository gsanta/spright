#pragma once

#include <set>
#include "flood_fill_range.h"
#include "flood_fill_range_queue.h"
#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/renderable/sprite.h"
#include "../../../engine/graphics/renderable/renderable2d.h"
#include "../../../engine/maths/vec2.h"

namespace spright_app {

	//type FillerData = {
 // width: number;

 // height: number;

 // pixels: number[];

 // point: Point;

 // targetColor: number;

 // replacementColor: number;

 // selectionThreshold ? : number;
	//};

	using namespace spright_engine::graphics;
	using namespace spright_engine::maths;


	struct FloodFillData {
		int width;
		int height;

	};

	class QueueLinearFloodFill {
	private:
		FloodFillData m_Data;
		FloodFillRangeQueue m_Queue;
		std::set<int> m_VisitedIndexes;
		bool m_IsEmptyTile;
		int m_SourceColor;
	public:
		void floodFill(TileLayer* layer, int x, int y, int color);
	private:
		void linearFill(TileLayer* layer, int x, int y, int color);
		bool checkPoint(TileLayer* layer, int x, int y, int color);
		bool isPixelWithinColorTolerance(TileLayer* layer, int tileIndex);
		void setColor(TileLayer* layer, int x, int y, int color);
	};

}