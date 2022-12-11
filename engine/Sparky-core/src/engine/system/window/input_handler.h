#pragma once

#include <vector>
#include "input_listener.h"
#include "window.h"
#include "../../maths/vec2.h"

using namespace std;

namespace spright_engine { namespace system {

	class Window;

	class InputHandler
	{
	private:
		vector<InputListener*> m_Listeners;
		Window* m_Window;

	public:
		InputHandler(Window* window);
		~InputHandler();
		void emitMouseDown(bool buttons[3]);
		void emitMouseUp(bool buttons[3]);
		void emitMouseMove(double x, double y);
		void emitScroll(double x, double y);
		void emitKeyChange(int key, bool isPressed);

		void registerListener(InputListener* inputListener);
		void unRegisterListener(InputListener* inputListener);
	
		spright_engine::maths::Vec2 screenToCanvasPos(spright_engine::maths::Vec2 screenPos);
	};

}}
