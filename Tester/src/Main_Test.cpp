#include <COG.h>

class TestLayer : public COG::Layer {

	COG::Game_Object object;

	std::shared_ptr<COG::Shader> shade;

	double total_delta = 0;

	std::vector<bool> is_key_down = std::vector<bool>(256);
	public:
	TestLayer() noexcept : Layer("Test Layer") {}

	virtual void on_detach() override {
		info("Detaching the test layer...");

		//Clean up this layer 
		object.~Game_Object();
		shade.~shared_ptr();

		COG::RenderResourceManager::unload_model("teapot");
		COG::RenderResourceManager::unload_shader("basic");
		COG::RenderResourceManager::unload_model("square");
	}

	virtual void on_attach() override {
		info("Attaching the test layer...");

		using namespace COG;
		RenderResourceManager::load_model("res/models/teapot.obj", "teapot");
		RenderResourceManager::load_shader("res/shaders/basic.shader", "basic", true);

		RenderResourceManager::load_model("", "square");
		if(!RenderResourceManager::get_model("square")->load_square(5)) {
			error("Could not set up a square!");
		}
		
		//The defaults for any object are as follows
		//position({0})
		//rotation(0, {0,0,1})
		//scale({1})
		
		object = Game_Object("teapot", "basic");
		shade = RenderResourceManager::get_shader("basic");
	}

	virtual void on_update(double delta) override {
		total_delta += delta;

		auto clamp = [ ](double val) -> float {
			if(val >= 1) {
				return 1;
			} else if(val <= 0) {
				return -static_cast<float>(val);
			}
			return static_cast<float>(val);
		};

		shade->use();
		shade->setUniform4f("u_color", .5, clamp(cos(total_delta)),
							clamp(sin(total_delta)), 1);


		if(is_key_down.at(' ')) {
			object.halt();
		} else {
			Vec3d moveDir;

			if(is_key_down.at('A')) {
				moveDir += {-1, 0, 0};
			} else if(is_key_down.at('D')) {
				moveDir += {1, 0, 0};
			}

			if(is_key_down.at('W')) {
				moveDir += {0, 1, 0};
			} else if(is_key_down.at('S')) {
				moveDir += {0, -1, 0};
			}

			moveDir *= 2;
			object.move(moveDir);
		}

		object.update(delta);
	}

	virtual void on_event(COG::Event& e) override {
		/*if(e.type() == COG::EventType::MousePress) {
			//Mouse press
			const auto& mp = COG::event_cast<COG::MouseButtonPressedEvent>(e);
			e.handled = true;
		} else if(e.type() == COG::EventType::KeyPressed) {
			//Key Press
			const auto& kp = COG::event_cast<COG::KeyPressedEvent>(e);
			is_key_down[kp.keycode()] = true;
			e.handled = true;
		} else if(e.type() == COG::EventType::KeyReleased) {
		   //Key Release
			const auto& kp = COG::event_cast<COG::KeyReleasedEvent>(e);
			is_key_down[kp.keycode()] = false;
			e.handled = true;
		} */

		using namespace COG;
		switch(e.type()) {
			case EventType::MousePress:	break;
			case EventType::KeyPressed:
				is_key_down[event_cast<KeyPressedEvent>(e).keycode()] = true;
				e.handled = true;
				break;
			case EventType::KeyReleased:
				is_key_down[event_cast<KeyReleasedEvent>(e).keycode()] = false;
				e.handled = true;
				break;
			default:
				break;
		}

	}
};

int main() {

	COG::COG_Engine cog;

	cog.set_clear_color(0, 0, 0);
	//cog.set_projection_perspective(90, cog.aspect_ratio());
	cog.set_ortho_from_center(20);

	cog.layer_stack().push_layer(std::make_shared<TestLayer>());

	info("Engine ready");

	cog.run();

}