#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shaders.h"
#include "Window.h"
#include "VAO.h"
#include "VBO.h"
#include "Circles.h"
#include "Circle.h"
#include "Physics.h"

int main() {
	

	//Circle Primitve Vertices
	float vertices[] = {
-1.0f, -1.0f,  // bottom-left
 3.0f, -1.0f,  // bottom-right (off screen)
-1.0f,  3.0f   // top-left (off screen)
	};


	Window Window1(Window::enScreenMode::FullScreen, "Chilling");
	Window1.StartWindow();

	Shaders Shader("default.dert","default.frag");
	// Generate the VAO and VBO with only 1 object each
	VAO VAO1;
	VBO VBO1;

	VAO1.Bind();
	VBO1.Bind();

	VBO1.IntroduceVertices(vertices,sizeof(vertices));
	
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	VAO1.Unbind();
	VBO1.Unbind();

	GLuint CenterLocation = glGetUniformLocation(Shader.ID, "u_Center");
	GLuint ColorLocation = glGetUniformLocation(Shader.ID, "u_Color");

	Circles CircleArray(100, Window1.getwidth(), Window1.getheight(), -0.5f, 4.0f);

	while (Window1.isWindowActive()){

		Window1.LoadWindowBG();

		Shader.Activate();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		Physics::SolveUsingSpatial(CircleArray, CircleArray.NumCircles(), Window1.getwidth(), Window1.getheight(), 50.0f);

		//Update
		for (size_t i = 0;i < CircleArray.NumCircles();++i) {
			CircleArray[i]->SetNewPosition(CircleArray[i]->getPosition().x + CircleArray[i]->getVelocity().x,
				CircleArray[i]->getPosition().y + CircleArray[i]->getVelocity().y);
				Shader.LoadCirclePositionToBackBuffer(CircleArray[i]);
		}

		// Swap the back buffer with the front buffer
		Window1.SwapBuffers();
		// Take care of all GLFW events
		Window1.GetEventsOnWindow();
	}

	Shader.Delete();
	VAO1.Delete();
	VBO1.Delete();

	Window1.TerminateWindow();
	
	return 0;
}
