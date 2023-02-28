
#include "gl_renderer2d.h"

namespace spright { namespace engine {

	GLRenderer2D::GLRenderer2D(GLShader shader): m_Shader(shader) {
		m_TransformationStack.push_back(Mat4::identity());
		m_TransformationBack = &m_TransformationStack.back();
		init();
	}

	GLRenderer2D::~GLRenderer2D() {
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	void GLRenderer2D::init() {
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glDepthMask(GL_FALSE);
		
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *) (offsetof(VertexData, color)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 2;
			indices[i + 2] = offset + 1;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 0;
			indices[i + 5] = offset + 3;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		
		glBindVertexArray(0);

//#ifdef SPARKY_EMSCRIPTEN
		m_BufferBase = new VertexData[RENDERER_MAX_SPRITES * 4];
//#endif
	}

	void GLRenderer2D::begin()
	{	
		getShader().enable();
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

//#ifdef SPARKY_EMSCRIPTEN
		m_Buffer = m_BufferBase;
//#else
//		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//#endif
	}

	void GLRenderer2D::end()
	{
//#ifdef SPARKY_EMSCRIPTEN
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (m_Buffer - m_BufferBase) * RENDERER_VERTEX_SIZE, m_BufferBase);
		m_Buffer = m_BufferBase;
//#else
//		glUnmapBuffer(GL_ARRAY_BUFFER);
//#endif
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLRenderer2D::flush()
	{
		//for (int i = 0; i < m_TextureSlots.size(); i++) {
		//	glActiveTexture(GL_TEXTURE0 + i);
		//	glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		//}

		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
		getShader().disable();
	}

	Shader& GLRenderer2D::getShader()
	{
		return m_Shader;
	}
} }