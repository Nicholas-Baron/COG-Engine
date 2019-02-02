#pragma once

#include "precomp/precomp.h"
namespace COG {
	class Model {
		private:
		bool is3D;

		//Multiply to normalize the model size
		float normal_factor;

		inline void clean_data();
		inline void gen_buffers(bool textured = false);

		public:
		Model(const std::string& file, bool is3D = false);
		inline ~Model() noexcept { clean_data(); }

		//Scale by this to get all vertecies at most 1 magnitude.
		inline float scaleFactor() const noexcept { return normal_factor; }
		inline bool hasDepth() const noexcept { return is3D; }

		bool loadSquare(float sideLength, bool textured = false);
		bool load_model(const std::string& file);
	};
}