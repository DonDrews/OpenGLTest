//GL LIBRARIES
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "pngloader.h"
//returns an image of black and white pixels
//formatted as an interlaced array of ubytes
//RGBA
GLubyte* makeCheckerboard(int size)
{
	GLubyte* image = new GLubyte[size * size * 4];
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			//return either a 0 or a 255 depending on even or odd sum of coordinates
			image[4 * (size * i + j)] = ((i + j) % 2) * 255;
			image[4 * (size * i + j) + 1] = ((i + j) % 2) * 255;
			image[4 * (size * i + j) + 2] = ((i + j) % 2) * 255;
			image[4 * (size * i + j) + 3] = 255; //alpha channel
		}
	}
	return &image[0];
}
