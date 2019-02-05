#pragma once

#include "precomp/precomp.h"

#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/Buffers/IndexBuffer.h"

namespace COG {
	template<typename T>
	struct EZ_Array{
		T* data;
		unsigned size;

		EZ_Array() noexcept : size(0), data(nullptr) {}

		EZ_Array(unsigned size_in) : size(size_in){
			data = new T[size];
		}

		~EZ_Array() {
			//delete[] data;
		}

		T& operator[](unsigned pos) {
			return data[pos];
		}
	};
	
	class Model {
		private:
		bool is3D;

		//Multiply to normalize the model size
		float normal_factor = 0;

		EZ_Array<float> vertex_buffer;
		EZ_Array<unsigned> indicies;

		std::unique_ptr<COG::VertexArray> va;
		std::unique_ptr<COG::VertexBuffer> vb;
		std::unique_ptr<COG::IndexBuffer> ib;
		
		inline void clean_data();
		inline void gen_buffers(bool textured = false);

		public:
		Model(const std::string& file, bool is3D = false);

		//Scale by this to get all vertecies at most 1 magnitude.
		inline float scale_factor() const noexcept { return normal_factor; }
		inline bool has_depth() const noexcept { return is3D; }

		bool load_square(float sideLength, bool textured = false);
		bool load_model(const std::string& file);
		COG_API void draw() const;
	};
}