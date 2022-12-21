#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "../../system/utils/fileUtils.h"
#include "../../../maths/vec2.h"
#include "../../../maths/mat4.h"

namespace engine { namespace graphics {
	using namespace spright::maths;

	class Shader {
	public:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1iv(const GLchar* name, int* value, int count);
		void setUniform1fv(const GLchar* name, float* value, int count);
		void setUniform2f(const GLchar* name, const Vec2& vector);
		void setUniform3f(const GLchar* name, const engine::maths::Vec3& vector);
		void setUniform4f(const GLchar* name, const engine::maths::Vec4& vector);
		void setUniformMat4(const GLchar* name, const Mat4& matrix);

		void enable() const;
		void disable() const;

	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};
} }