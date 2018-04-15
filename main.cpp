#include"src\tgaimage.h"
#include "src\Renderer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "src\utils\tiny_obj_loader.h"
#include "src\math\Vector3.h"
#include <vector>
#include "src\math\Matrix44.h"

using namespace Math;

uint32_t h = 800, w = 800;

Renderer r(w, h);
vec3f world2screen(vec3f v) {
	return vec3f(int((v.x + 1.)*w / 2. + .5), int((v.y + 1.)*h / 2. + .5), v.z);
}
int main()
{

	const TGAColor c(255, 0, 0, 255);
	TGAImage img;
	img.read_tga_file("../obj/african_head/african_head_diffuse.tga");

	vec3f lightDir(0, 0, -1);
	vec3f lightColor(1, 1, 1);


	std::string inputfile = "../obj/african_head/african_head.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	std::vector<Vertex> rasterCoords(3);
	std::vector<Vertex> worldCoords(3);

	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex

				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				worldCoords[v].pos.x = attrib.vertices[3 * idx.vertex_index + 0];
				worldCoords[v].pos.y = attrib.vertices[3 * idx.vertex_index + 1];
				worldCoords[v].pos.z = attrib.vertices[3 * idx.vertex_index + 2];
				worldCoords[v].uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
				worldCoords[v].uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];

				if (worldCoords[v].uv.x < -1.0f || worldCoords[v].uv.y < -1.0f) 
				{
					int kkk = 0;
				}
				//rasterCoords[v].z = 1 / vert.z;
				/*	tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				;*/

			}
			mat44f projection;
			projection.Perspective(Math::ToRadian(90.0f), 1000.f, 0.01f, (float)w / (float)h);




			rasterCoords[0].pos.x = (worldCoords[0].pos.x + 1.0f)*w*0.5f + 0.5f;
			rasterCoords[0].pos.y = (worldCoords[0].pos.y + 1.0f)*h*0.5f + 0.5f;
			rasterCoords[0].pos.z = -1 / worldCoords[0].pos.z;
			rasterCoords[0].uv = worldCoords[0].uv*rasterCoords[0].pos.z;

			rasterCoords[1].pos.x = (worldCoords[1].pos.x + 1.0f)*w*0.5f + 0.5f;
			rasterCoords[1].pos.y = (worldCoords[1].pos.y + 1.0f)*h*0.5f + 0.5f;
			rasterCoords[1].pos.z = -1 / worldCoords[1].pos.z;
			rasterCoords[1].uv = worldCoords[1].uv *rasterCoords[1].pos.z;

			rasterCoords[2].pos.x = (worldCoords[2].pos.x + 1.0f)*w*0.5f + 0.5f;
			rasterCoords[2].pos.y = (worldCoords[2].pos.y + 1.0f)*h*0.5f + 0.5f;
			rasterCoords[2].pos.z = -1.0f / worldCoords[2].pos.z;
			rasterCoords[2].uv = worldCoords[2].uv*rasterCoords[2].pos.z;



			vec3f triangleNormal = Vector3<float>::Cross(worldCoords[2].pos - worldCoords[0].pos, worldCoords[1].pos - worldCoords[0].pos).Normalize();
			float inten = Vector3<float>::Dot(triangleNormal, lightDir);
			
			if (inten > 0)
			{
				// TGAColor(255 * inten, 255 * inten, inten * 255, 255)

				r.FillTriangle(rasterCoords[0], rasterCoords[1], rasterCoords[2],img);
			}

			index_offset += fv;
		}




		r.WriteToFile("../img.tga");
		return 0;
	}
}