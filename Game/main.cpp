//#include "InputManager.h"
#include "display.h"
#include "game.h"
#include "glm\glm.hpp"
#include <stb_image.h>
#include "assignment.h"

int main(int argc,char *argv[])
{
	const int DISPLAY_WIDTH = 512; //1600;
	const int DISPLAY_HEIGHT = 512; //800;
	const float CAMERA_ANGLE = 0.0f;
	const float NEAR = 1.0f;
	const float FAR = 100.0f;

	Game *scn = new Game(CAMERA_ANGLE,(float)DISPLAY_WIDTH/DISPLAY_HEIGHT,NEAR,FAR);
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	//Init(display);

	// lena as is
	int width, height, numComponents;
	unsigned char* data0 = stbi_load("../lena256.jpg", &width, &height, &numComponents, 4);
	
	// Canny Edge Detection
	unsigned char* data1 = Canny_Edge_Detector(data0, width, height);
	
	// Halftone
	unsigned char* data2 = halftone(data0, width, height);
	
	// Floyd-Steinberg Algorithm
	unsigned char* data3 = Floyd_Steinberg_Algorithm(data0, width, height);

	scn->AddTexture(width*2, height*2, data2); // texture 0
	scn->AddTexture(width, height, data3);     // texture 1
	scn->AddTexture(width, height, data1);     // texture 2
	scn->AddTexture(width, height, data0);     // texture 3

	scn->Init();

	display.SetScene(scn);
	
	int half = DISPLAY_WIDTH / 2;

	// texture 0
	scn->SetShapeTex(0, 0);
	glViewport(0, 0, half, half);
	scn->Draw(1, 0, scn->BACK, true, false);

	// texture 1
	scn->SetShapeTex(0, 1);
	glViewport(half, 0, half, half);
	scn->Draw(1, 0, scn->BACK, false, false);

	// texture 2
	scn->SetShapeTex(0, 2);
	glViewport(half, half, half, half);
	scn->Draw(1, 0, scn->BACK, false, false);

	// texture 3
	scn->SetShapeTex(0, 3);
	glViewport(0, half, half, half);
	scn->Draw(1, 0, scn->BACK, false, false);

	display.SwapBuffers();
	
	while (!display.CloseWindow())
		display.PollEvents();

	delete scn;
	return 0;
}
