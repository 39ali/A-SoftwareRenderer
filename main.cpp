#include <fstream>
#include "src\math\Vector3.h"
struct Rgb 
{
	unsigned char r, g, b;
};

float EdgeFunction(const vec3f& a, const vec3f&b, const vec3f&p) 
{
	return (p.x - a.x)*(b.y - a.y) - (p.y - a.y)*(b.x - a.x);
}

int main() 
{
	const uint32_t w = 512;
	const uint32_t h = 512;
	std::ofstream ofs("../img.ppm",std::ios::binary);
	ofs << "P6 " << w << " " << h << " " << "255 /n";

	vec3f v0(100,100,0);
	vec3f v1(100, 450, 0);
	vec3f v2(300, 225, 0);
	vec3f c0(1, 0, 0);
	vec3f c1(0, 1, 0);
	vec3f c2(0, 0, 1);
	Rgb framebuffer[w*h];
	float area = EdgeFunction(v0, v1, v2);
	for (uint32_t j = 0; j < h; j++) 
	{
		for (uint32_t i = 0; i < w; i++) 
		{	
			vec3f p(i + 0.5f,j +0.5f,0);
			float w0 = EdgeFunction(v0, v1, p);
			float w1 = EdgeFunction(v1, v2, p);
			float w2 = EdgeFunction(v2, v0, p);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0) 
			{
			
				w0 /= area;
				w1 /= area;
				w2 /= area;
				
				float r = w0*c0.x + w1*c1.x + w2*c2.x;
				float g = w0*c0.y + w1*c1.y + w2*c2.y;
				float b = w0*c0.z + w1*c1.z + w2*c2.z;

				framebuffer[j*w + i].r = (unsigned char)(255 * r);
				framebuffer[j*w + i].g = (unsigned char)(255 * g);
				framebuffer[j*w + i].b = (unsigned char)(255 * b);
			}
		}
	}

	ofs.write((char*)framebuffer, w*h*3);
	ofs.close();
}