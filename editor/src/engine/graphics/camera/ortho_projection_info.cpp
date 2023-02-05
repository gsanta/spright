#include "ortho_projection_info.h"

namespace engine { namespace graphics {
	OrthoProjectionInfo::OrthoProjectionInfo(Dimensions dimensions, float near, float far): left(dimensions.left), right(dimensions.right), bottom(dimensions.bottom), top(dimensions.top), near(near), far(far)
	{

	}

	OrthoProjectionInfo::OrthoProjectionInfo() {}

	void OrthoProjectionInfo::setSize(float newWidth, float newHeight)
	{
		float deltaWidth = (newWidth - getWidth()) / 2.0f;

		left -= deltaWidth;
		right += deltaWidth;


		float deltaHeight = (newHeight - getHeight()) / 2.0f;

		top += deltaHeight;
		bottom -= deltaHeight;
	}

	float OrthoProjectionInfo::getWidth() const {
		return right - left;
	}

	float OrthoProjectionInfo::getHeight() const {
		return top - bottom;
	}
}}
