#pragma once
#include <GL/glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float w, float h);
	void Draw();

private:
	float _x;
	float _y;
	float _w;
	float _h;

	GLuint _vboID;
};

