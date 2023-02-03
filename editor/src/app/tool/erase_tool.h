#pragma once

#include <vector>
#include "../../engine/graphics/renderable/rect2d.h"
#include "../../engine/graphics/renderable/renderable2d.h"
#include "../document/document_handler.h"
#include "tool.h"
#include "../service/core/event/event_handler.h"

namespace spright { namespace tool {
	using namespace spright::maths;
	using namespace ::engine::graphics;
	using namespace document;

	class EraseTool : public Tool {
	private:
		DocumentHandler* m_DocumentHandler;
		EventHandler* m_EventHandler;
		vector<Rect2D*> m_SelectionSprites;

		Rect2D* m_TopLine = nullptr;
		Rect2D* m_RightLine = nullptr;
		Rect2D* m_BottomLine = nullptr;
		Rect2D* m_LeftLine = nullptr;

		int m_EraserSize = 3;

		float m_DashSize = 0.2f;
		bool m_IsMoveSelection = false;

		float m_NoMovementTolerance = 0.1f;

	public:
		EraseTool(DocumentHandler* documentHandler, EventHandler* eventHandler);
		void pointerMove(PointerInfo& pointerInfo) override;
		void activate() override;
		void deactivate() override;
	private:
		void setEraserPosition(PointerInfo& pointerInfo);
		void erase(PointerInfo& pointerInfo);
	};
}}