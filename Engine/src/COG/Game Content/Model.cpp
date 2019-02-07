#include "precomp/precomp.h"
#include "Model.h"

#include "obj_loader/OBJ_Loader.h"

#include "Rendering/RenderUtil.h"
#include "Rendering/VertexArray.h"

inline void COG::Model::clean_data() {
	indicies.erase(indicies.begin(), indicies.end());
	vertex_buffer.erase(vertex_buffer.begin(), vertex_buffer.end());
}

inline void COG::Model::gen_buffers(bool textured) {
	
	vb = std::make_unique<VertexBuffer>(vertex_buffer.data(), vertex_buffer.size() * sizeof(float));

	VertexBufferLayout* vbl = new VertexBufferLayout;
	vbl->push<float>(2 + is3D);
	if(textured) { vbl->push<float>(2); }

	va = std::make_unique<COG::VertexArray>();
	va->add_buffer(vb.get(), vbl);

	ib = std::make_unique<IndexBuffer>(indicies.data(), indicies.size());
}

COG::Model::Model(const std::string & file, bool is3D) : is3D(is3D) {
	
	if(!file.empty()) {

		info_internal("Loading model from " + file);
		if(load_model(file)) {
			info_internal("Successfully loaded " + file);
		} else {
			COG_ASSERT_INTERNAL(false, "File " + file + " could not be loaded!");
		}
	}
}

bool COG::Model::load_square(float sideLength, bool textured) {
	if(sideLength <= 0) {
		return false;
	}

	clean_data();

	const auto half_length = sideLength / 2;

	if(!textured) {

		//vertex_buffer.size = 8;
		vertex_buffer = {
		-half_length, -half_length,
			half_length, -half_length,
			half_length, half_length,
			-half_length, half_length
		};
	} else {
		
		//vertex_buffer.size = 16;
		vertex_buffer = {
			-half_length, -half_length,
			0, 1,
			half_length, -half_length,
			1, 1,
			half_length, half_length,
			1, 0,
			-half_length, half_length,
			0, 0
		};
	}

	//indicies.size = 8;
	indicies = {
	0, 1, 2,
		2, 3, 0
	};

	is3D = false;
	normal_factor = 1;
	gen_buffers(textured);

	return true;
}

bool COG::Model::load_model(const std::string & file) {
	objl::Loader loader;

	if(loader.LoadFile(file)) {
		clean_data();

		auto magnitude_squared = [](const objl::Vector3& vec) -> float {
			return (vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z);
		};
		
		vertex_buffer.reserve(loader.LoadedVertices.size() * 3);
		
		float farthest_vertex_squared = 0;
		for(const auto& vert : loader.LoadedVertices) {
			const auto& data = vert.Position;

			vertex_buffer.push_back(data.X);
			vertex_buffer.push_back(data.Y);
			vertex_buffer.push_back(data.Z);

			farthest_vertex_squared = std::max(magnitude_squared(data), farthest_vertex_squared);
		}

		normal_factor = 1 / sqrtf(farthest_vertex_squared);

		indicies.reserve(loader.LoadedIndices.size());
		for(const auto& val : loader.LoadedIndices){
			indicies.push_back(std::move(val));
		}

		is3D = true;
		gen_buffers();

		return true;
	}

	return false;
}

void COG::Model::draw() const {
	va->bind();
	ib->bind();
	COG_ASSERT_INTERNAL(ib->count() > 2, "What shape has 2 or fewer indicies?");
	GLCALL(glDrawElements(GL_TRIANGLES, ib->count(), GL_UNSIGNED_INT, NULL));
}

