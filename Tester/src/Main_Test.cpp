#include <COG.h>

class TestLayer : public COG::Layer{
	
	COG::Game_Object object;

	std::shared_ptr<COG::Shader> shade;
	public:
	TestLayer() : Layer("Test Layer") {}

	virtual void on_detach() override {
		info("Detaching the test layer...");
		object.~Game_Object();
		shade.~shared_ptr();
		COG::RenderResourceManager::unload_model("teapot");
		COG::RenderResourceManager::unload_shader("basic");
	}

	virtual void on_attach() override {
		info("Attaching the test layer...");
		COG::RenderResourceManager::load_model("res/models/teapot.obj", "teapot");
		COG::RenderResourceManager::load_shader("res/shaders/basic.shader", "basic", true);
		
		COG::RenderResourceManager::load_model("", "square");
		if(!COG::RenderResourceManager::get_model("square")->load_square(10)){
			error("Could not set up a square!");
		}

		object = COG::Game_Object("square", "basic");
		//object.set_position({0, 0, 5});
		//object.set_rotation(3.14f/2, {0,0,1});
		object.set_scale({1});

		shade = COG::RenderResourceManager::get_shader("basic");
	}

	virtual void on_update(double delta) override{	
		static double total_delta = 0;
		total_delta += delta;
		
		shade->use();
		shade->setUniform4f("u_color", 0, 0, 1, 1);
		object.set_rotation(std::cos(total_delta), {0, std::sin(total_delta), 0});
		//object.set_position({std::cos(total_delta), std::sin(total_delta), 0});
		object.update(delta);
	}

	virtual void on_event(COG::Event& e) override {
		if(e.type() == COG::EventType::MousePress) {
			//Mouse press
			const auto& mp = COG::event_cast<COG::MouseButtonPressedEvent>(e);
			info(mp.mouse_button());
			e.handled = true;
		} else if(e.type() == COG::EventType::KeyTyped) {
			//Key Press
			const auto& kp = COG::event_cast<COG::KeyTypedEvent>(e);
			info(kp.keycode());
			e.handled = true;
		}
	}
};

int main() {

	COG::COG_Engine cog;
	
	//cog.set_clear_color(0,0,0);
	//cog.set_projection_perspective(90, cog.aspect_ratio());
	cog.set_ortho_from_center(100);
	cog.layer_stack().push_layer(std::make_shared<TestLayer>());

	info("Engine ready");

	cog.run();

}