#pragma once

#include <cstddef>
#include "../../renderer/renderer2d.h"
#include "../../renderer/vertex_data.h"
#include "../../buffer/vertexArray.h"
#include "../../buffer/indexBuffer.h"
#include "../../renderable/renderable2d.h"

namespace spright { namespace engine {
	using namespace ::engine::graphics;

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE *RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

	class GLRenderer2D : public Renderer2D
	{
	private:
		GLuint m_VBO;
		GLuint m_VAO;
		IndexBuffer *m_IBO;
		//#ifdef SPARKY_EMSCRIPTEN
		VertexData *m_BufferBase;
		//#endif
		VertexData *m_Buffer;
		std::vector<GLuint> m_TextureSlots;

	public:
		GLRenderer2D();
		~GLRenderer2D();
		inline virtual VertexData *&getBuffer()
		{
			return m_Buffer;
		}
		void begin() override;
		void end() override;
		void flush() override;

	private:
		void init();
	};
	}
}
