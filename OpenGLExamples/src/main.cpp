#include "OpenGLExamplesApplication.h"

int main()
{

	OpenGLCore::WindowInfo windowInfo;
	windowInfo.Width = 1024;
	windowInfo.Height = 768;
	windowInfo.Title = "Hello World";

	OpenGLExamples::OpenGLExamplesApplication app;

	if (app.Run(windowInfo))
		return EXIT_SUCCESS;
	
	return EXIT_FAILURE;
}