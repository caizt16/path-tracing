// Example main.

using namespace std;
#include <math.h>
#include <iostream>
#include "integrator.h"
#include "visualizer.h"

int main(int argc, char** argv) {
	// Load up an STL file.
	auto scene = new Scene(argv[1]);
	// Make a light.
	scene->lights->push_back(Light({Vec(0, 0, 3), 9.0 * Vec(0.8, 0.5, 0.25)}));
	scene->lights->push_back(Light({Vec(-2, 2, 4), 9.0 * Vec(0.25, 0.8, 0.25)}));
	scene->lights->push_back(Light({Vec(-2, -2, 4), 9.0 * Vec(0.25, 0.25, 0.8)}));
	scene->camera_image_plane_width = 0.5 * 1.5;
	scene->plane_of_focus_distance = 4.5;
	scene->dof_dispersion = 0.1;

	start_performance_counter();

	auto engine = new RenderEngine(1366, 768, scene);
	engine->tile_width = 64;
	engine->tile_height = 64;

	for (int frame = 0; frame < 100; frame++) {
		engine->zero();
		Real angle = 20.0 * 0.05; //frame * 0.05;
//		Real angle = frame * 0.05;
		scene->main_camera.origin = -5 * Vec(cos(angle), sin(angle), 0.0);
		scene->main_camera.direction = -scene->main_camera.origin;
		scene->main_camera.direction.normalize();
		scene->main_camera.origin += Vec(0.0, 0.0, 0.2);
		scene->plane_of_focus_distance = 3.5 + frame / 33.0;

		auto display = new ProgressBar(engine);
//		display->init();

		engine->perform_full_passes(100);
		display->main_loop();
		engine->sync();
		engine->rebuild_master_canvas();

		char output_path[80];
		sprintf(output_path, "massive/frame%04i.png", frame);
		engine->master_canvas->save(output_path);
		delete display;
	}

	delete engine;

	cout << "Total time to render: ";
	print_performance_counter();
	cout << endl;
	cout << "Rays cast: " << rays_cast << endl;
	cout << "Triangle tests: " << triangle_tests << endl;

	delete scene;
}

