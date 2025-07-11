#include "Window.h"

	Window::Window(enScreenMode enVarScreenMode, const char *WindowName) {

		__init();

		__setPrimaryMonitorSpecifications();
	
		//Maybe a class function to intialize class properties in the future
		WindowMode = enVarScreenMode;
		this->WindowName = WindowName;

	}


		void Window::SwapBuffers() {
			glfwSwapBuffers(__window);
	};
		
		void Window::GetEventsOnWindow() {
			//Get events happen on the window
			glfwPollEvents();
		}
	    void Window::LoadWindowBG() {

		glClearColor(0.05f, 0.07f, 0.10f, 1.0);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
	}

		void Window::StartWindow() {


			switch (WindowMode)
			{
			case FullScreen:
				__setFullScreenWindowHints();

				if(!__StartFullScreenWindow(WindowName)) {
					throw std::runtime_error("Failed to set a full screen window!");
				}
				else {

					//Set and load data buffer for fullscreen mode
					__setDefaultWindowBuffer();
					
					glViewport(0, 0, __mode->width, __mode->height);
				}

				break;
			default:
				//some default code here
				break;
			}
			//height +1

			//private function to encapsulate the function expression
		}

		void Window::TerminateWindow() {
			Window::__terminateWindow();
		}

		void Window::__init() {

			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void Window::__setPrimaryMonitorSpecifications() {
			__primaryMonitor = glfwGetPrimaryMonitor(); // <== a pointer for the primary monitor
			__mode =  glfwGetVideoMode(__primaryMonitor);
		}


		//Hints
		void Window::__setFullScreenWindowHints() {
			glfwWindowHint(GLFW_RED_BITS, __mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, __mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, __mode->blueBits);

			glfwWindowHint(GLFW_REFRESH_RATE, __mode->refreshRate);

			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // <== No window border
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // <== Not resizable
		}

		//Buffers

		void Window::__setDefaultWindowBuffer() {

			//Glad init
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //RGBA = white
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(__window);
		}

		bool Window::__StartFullScreenWindow(const char* WindowName) {

			 __window = glfwCreateWindow(__mode->width, __mode->height, WindowName, NULL, NULL);
			 __UpdateIsWindowActive();

			if (__window == NULL) {
				glfwTerminate();
				return false;
			}
			//context is like an execution context object 
			glfwGetFramebufferSize(__window, &width, &height);
			glfwMakeContextCurrent(__window);
			gladLoadGL();

			return true;
		}


		void Window::__terminateWindow() {
			glfwDestroyWindow(__window);
			glfwTerminate();
		}
		

		void Window::__UpdateIsWindowActive() {
			//Consider stack issue here to be asked ----------------------------- Important
			if(__window!=NULL)
			__isWindowActive = !glfwWindowShouldClose(__window);
		}
		//!glfwWindowShouldClose(__window)
		//Getters

		bool Window::isWindowActive() {
			__UpdateIsWindowActive();
			return __isWindowActive;
		}

		int Window::getwidth() {
			return width;
		}
		
		int Window::getheight() {
			return height;
		}
	
		Window::MouseState mouseState;


		//Coming right/left click
		//void Window::__mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		//	if (action == GLFW_PRESS) {
		//		mouseState.lastButton = button;
		//		mouseState.hasNewClick = true;
		//	}
		//}

		//int Window::getClickedButton() {

		//	if (mouseState.hasNewClick) {
		//		mouseState.hasNewClick = false;

		//		// Check which button was clicked and return corresponding number
		//		if (mouseState.lastButton == GLFW_MOUSE_BUTTON_LEFT) return 1;
		//		if (mouseState.lastButton == GLFW_MOUSE_BUTTON_RIGHT) return -1;
		//		// Could add more buttons here if needed (middle button, etc.)
		//	}
		//	return 0; // No click detected
		//}

		//int Window::OnMouseClick() {
		//	glfwSetMouseButtonCallback(__window, __mouse_button_callback);
		//	return Window::getClickedButton();
		//}

