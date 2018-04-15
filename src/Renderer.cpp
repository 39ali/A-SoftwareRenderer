#include "Renderer.h"


Renderer::Renderer(unsigned int w, unsigned int h) :m_Img(w, h, TGAImage::RGB), m_h(h), m_w(w)
{
	m_zBuffer = new float[m_w*m_h];
	const float s = std::numeric_limits<float>::max();
	for (uint32_t i = 0; i < m_w*m_h; i++)
	{
		m_zBuffer[i] = s;
	}
}


void Renderer::DrawLine(int x1, int y1, int x2, int y2, const TGAColor& c)
{
	int dx = std::abs(x1 - x2);
	int dy = std::abs(y1 - y2);
	bool st = false;
	if (dx < dy)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
		st = true;
	}
	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	int err = 0, m = 2 * std::abs(dy);

	for (int x = x1; x <= x2; x++)
	{
		if (st)
		{
			m_Img.set(y, x, c);
		}
		else
		{
			m_Img.set(x, y, c);
		}
		err += m;
		if (err > dx)
		{
			y += (y2 > y1) ? 1 : -1;
			err -= 2 * dx;
		}
	}
}

float Renderer::LineEdge(const vec3f& v1, const vec3f& v2, const vec3f& v3) const
{
	return (v3.x - v1.x) *(v2.y - v1.y) - (v3.y - v1.y)*(v2.x - v1.x);
}



vec3f Renderer::barycentric(const vec3f& A, vec3f B, const vec3f& C, const vec3f& P)
{

	vec3f u = vec3f::Cross(vec3f(C.x - A.x, B.x - A.x, A.x - P.x),
		vec3f(C.y - A.y, B.y - A.y, A.y - P.y));
	return vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}




void Renderer::FillTriangle(Vertex& v0, Vertex& v1, Vertex& v2, TGAImage& img)
{
	vec2i bboxmin;
	vec2i bboxmax;
	bboxmin.x = std::max(0.0f, std::min(std::min(v0.pos.x, v1.pos.x), v2.pos.x));
	bboxmin.y = std::max(0.0f, std::min(std::min(v0.pos.y, v1.pos.y), v2.pos.y));

	bboxmax.x = std::min((m_w - 1.0f), std::ceil(std::max(std::max(v0.pos.x, v1.pos.x), v2.pos.x)));
	bboxmax.y = std::min((m_h - 1.0f), std::ceil(std::max(std::max(v0.pos.y, v1.pos.y), v2.pos.y)));




	vec3f P;
	for (uint32_t x = bboxmin.x; x < bboxmax.x; x++)
	{
		for (uint32_t y = bboxmin.y; y < bboxmax.y; y++)
		{
			vec3f P(x + 0.5f, y + 0.5f, 0.f);
			vec3f vv = barycentric(v0.pos, v1.pos, v2.pos, P);

			if (vv.x < 0 || vv.y < 0 || vv.z < 0) continue;

			P.z = 1 / (vv.x* v0.pos.z + vv.y * v1.pos.z + vv.z * v2.pos.z);

			float u = (vv.x *v0.uv.x + vv.y*v1.uv.x + vv.z*v2.uv.x)*img.get_width()*P.z;
			float v = (vv.x *v0.uv.y + vv.y*v1.uv.y + vv.z*v2.uv.y)*img.get_height()*P.z;

			TGAColor c = img.get(u, v);


			if (m_zBuffer[x + m_w * y] > P.z)
			{
				m_zBuffer[x + m_w * y] = P.z;

				m_Img.set(P.x, P.y, c);
			}


		}
	}


}


void Renderer::WriteToFile(const char* dir)
{
	m_Img.flip_vertically();
	m_Img.write_tga_file(dir);
}
