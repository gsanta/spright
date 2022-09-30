#include "brush_tool.h"

namespace my_app { namespace editor { namespace tool {

	BrushTool::BrushTool(DocumentHandler* documentHandler, EditorConfig& editorConfig) 
		: m_documentHandler(documentHandler), m_EditorConfig(editorConfig), Tool("brush")
	{

	}

	void BrushTool::pointerDown(PointerInfo& pointerInfo)
	{
		my_app::graphics::TileLayer* tileLayer = dynamic_cast<my_app::graphics::TileLayer*>(m_documentHandler->getActiveDocument()->getActiveLayer());
		my_app::maths::Vec2 tilePos = tileLayer->getTilePos(pointerInfo.curr);

		my_app::graphics::Sprite* sprite = new my_app::graphics::Sprite(tilePos.x, tilePos.y, tileLayer->getTileSize(), tileLayer->getTileSize(), 0xff0000ff);
		tileLayer->add(sprite);
	}
}}}
