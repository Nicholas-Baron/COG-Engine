#pragma once

//This file should NOT be included in other headers

#include "COG/Utils/Vec3d.h"
#include "Game_Object.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace COG {
	
	inline glm::vec3 vector_cast(const Vec3d& data){
		return {data.x_val(), data.y_val(), data.z_val()};
	}

	inline glm::mat4 translate_mat(const Game_Object* go) {
		return glm::translate(vector_cast(go->get_position()));
	}
	
	inline glm::mat4 scale_mat(const Game_Object* go) {
		auto vec = go->get_scale();
		debug_internal(std::to_string(vec));
		return glm::scale(vector_cast(go->get_scale()));
	}
	
	inline glm::mat4 rotation_mat(const Game_Object* go) noexcept {
		auto data = go->get_rotation();
		return glm::rotate(data.first, vector_cast(data.second));
	}
	
	inline glm::mat4 model_mat(const Game_Object* go) noexcept {

		auto rot = rotation_mat(go);
		auto trans = translate_mat(go);
		auto scale = scale_mat(go);
		auto combine = trans * rot * scale;
		/*for(int i = 0; i < combine.length(); i++) {
			for(int j = 0; j < combine[i].length(); j++) {
				debug_internal(combine[i][j]);
			}
		}*/ 
		if(combine == (glm::mat4() - glm::mat4())){
			if(combine == rot) {
				error_internal("Rotation is 0!");
			} else if(combine == scale) {
				error_internal("Scale is 0! " + std::to_string(scale[0][0]));
			} else if(combine == trans){
				error_internal("Trans is 0!");
			}	 
		}
		return combine;
	}  
}
