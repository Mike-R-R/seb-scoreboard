
#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"
#include "pixel-mapper.h"
#include "graphics.h"
#include "ScoreboardController.h"

#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <deque>

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
  interrupt_received = true;
}

int main(int argc, char *argv[]){
	std::cout << "******************************" << std::endl;
	std::cout << "* Running LED Matrix Program *" << std::endl;
	std::cout << "******************************" << std::endl;
	std::cout << "\n" << std::endl;

	rgb_matrix::RGBMatrix::Options matrix_options;
	rgb_matrix::RuntimeOptions runtime_opt;

	// These are the defaults when no command-line flags are given.
	matrix_options.rows = 32;
	matrix_options.chain_length = 1;
	matrix_options.parallel = 1;
	matrix_options.hardware_mapping = "adafruit-hat";

	rgb_matrix::RGBMatrix *matrix = CreateMatrixFromOptions(matrix_options, runtime_opt);
	if (matrix == NULL)
		return 1;

	std::cout << "Size: " << matrix->width() << " x " << matrix->height();
	std:: cout << "Hardware gpio mapping: " << matrix_options.hardware_mapping << std::endl;

	rgb_matrix::Canvas *canvas = matrix;
	
	// The ThreadedCanvasManipulator objects are filling
	// the matrix continuously.
	rgb_matrix::ThreadedCanvasManipulator* image_gen = NULL;

	image_gen = new ScoreboardController(canvas);
	
	// Set up an interrupt handler to be able to stop animations while they go
	// on. Note, each demo tests for while (running() && !interrupt_received) {},
	// so they exit as soon as they get a signal.
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	// Image generating demo is crated. Now start the thread.
	image_gen->Start();
	
	ScoreboardController* controller_pointer = dynamic_cast<ScoreboardController*>(image_gen);
	
	// Now, the image generation runs in the background. We can do arbitrary
	// things here in parallel.
	printf("Press <CTRL-C> to exit and reset LEDs\n");
	while (!interrupt_received && controller_pointer->running()) {
		sleep(1); // Time doesn't really matter. The syscall will be interrupted.
	}
	
	controller_pointer->stop_game();
	
	// Stop image generating thread. The delete triggers
	delete image_gen;
	delete canvas;

	std::cout << "\n" << std::endl;
	std::cout << "******************************" << std::endl;
	std::cout << "* Exiting LED Matrix Program *" << std::endl;
	std::cout << "******************************" << std::endl;

	return 0;
}
