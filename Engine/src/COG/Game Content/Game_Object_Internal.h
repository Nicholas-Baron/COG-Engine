#pragma once

//This file should NOT be included in other headers

#include "COG/Utils/Vec3d.h"
#include "Game_Object.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace COG {
	
	inline glm::vec3 vector_cast(const Vec3d& data){
		return {data.x_val(), data.y_val(), data.z_val()};
	}

	inline glm::mat4 translate_mat(const Game_Object* go) {
		return glm::translate(vector_cast(go->get_position()));
	}
	
	inline glm::mat4 scale_mat(const Game_Object* go) {
		return glm::scale(vector_cast(go->get_scale()));
	}
	
	inline glm::mat4 rotation_mat(const Game_Object* go) noexcept {
		auto data = go->get_rotation();
		glm::quat rot(vector_cast(data.second));
		//return glm::toMat4(rot);
		return glm::rotate(data.first, vector_cast(data.second));
	}
	
	glm::mat4 model_mat(const Game_Object* go) noexcept {

		auto rot = rotation_mat(go);
		auto trans = translate_mat(go);
		auto scale = scale_mat(go);
		auto combine = trans * rot * scale;

		static const auto zero_mat = glm::mat4() - glm::mat4();

		if(combine == zero_mat){
			if(combine == rot) {
				error_internal("Rotation is 0!");
			} else if(combine == scale) {
				error_internal("Scale is 0!");
			} else if(combine == trans){
				error_internal("Trans is 0!");
			}	 
		}

		return combine;
	}  
}
