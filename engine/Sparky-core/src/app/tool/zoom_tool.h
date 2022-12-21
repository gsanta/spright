#pragma once

#include "tool.h"
#include "../../engine/graphics/camera/camera.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"
#include "pointer_info.h"

namespace spright {

	class ZoomTool : public tool::Tool
	{
	private:
		engine::graphics::Camera* m_Camera;
		float m_ZoomFactor = 1.0f;

	public:
		ZoomTool(engine::graphics::Camera* camera);
	private:
		void scroll(tool::PointerInfo& pointerInfo) override;
	};
}
