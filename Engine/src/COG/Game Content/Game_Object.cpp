#include "precomp/precomp.h"
#include "Game_Object.h"
#include "RenderResourceManager.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"	

COG::Game_Object::Game_Object(const std::string & model_name, const std::string & shader) {
	
	model = RenderResourceManager::get_model(model_name);
	set_scale(Vec3d(model->scale_factor()));

	this->shader = RenderResourceManager::get_shader(shader);
}

/*void COG::Game_Object::shader_settings(const glm::mat4 & vpmat) const {
	shader->use();
	//shader->setUniformMat4f("u_MVP", vpmat * model_mat());
} */

//TODO: APPLY SCALE
void COG::Game_Object::update(double delta) {
	shader->use();
	//shader->setUniformMat4f("u_MVP", model_mat());
	model->draw();
}