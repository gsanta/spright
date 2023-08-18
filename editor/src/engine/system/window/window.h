#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "input_handler.h"
#include <functional>
#include "../../layout/container.h"

namespace spright { namespace engine {
	class InputHandler;

	class Window : public Container {
	public:
		inline Window(int width, int height): Container(Bounds(0, 0, width, height)) {}
		inline virtual ~Window() {}
		virtual void clear() const = 0;
		virtual float beforeRender() = 0;
		virtual void afterRender() = 0;
		virtual bool closed() const = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual void setSize(int width, int height) = 0;

		virtual bool isKeyPressed(unsigned int keycode) const = 0;
		virtual bool isMouseButtonPressed(unsigned int button) const = 0;
		virtual void getMousePosition(double& x, double& y) const = 0;
		virtual float getRatio() = 0;

		virtual InputHandler* getInputHandler() const = 0;
	};
}}
