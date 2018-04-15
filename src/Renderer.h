#pragma once
#include "tgaimage.h"
#include "math\Vector3.h"
#include "math\vector2.h"
#include <algorithm>
using namespace Math;

struct Vertex
{
	vec3f pos;
	vec2f uv;
};

class Renderer
{
public:
	Renderer(unsigned int w, unsigned int h);
	~Renderer() { delete[] m_zBuffer; };

	void DrawLine(int x1, int y1, int x2, int y2, const TGAColor& c);
	void Renderer::FillTriangle(Vertex& v0, Vertex& v1, Vertex& v2, TGAImage& img);
	void WriteToFile(const char* dir);


private:
	float Renderer::LineEdge(const vec3f& v1, const vec3f& v2, const vec3f& v3) const;
	vec3f Renderer::barycentric(const vec3f& A, vec3f B, const vec3f& C, const vec3f& P);
private:
	float* m_zBuffer;
	TGAImage m_Img;
	unsigned int m_w, m_h;
};