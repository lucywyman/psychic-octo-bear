#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

struct Inputs{
	float thermal_conductivity;
	float density;
	float specific_heat;
	float initial_temp; 
	float length; //Total length of wire
	int position_intervals; //Number of intervals
	float delta_x; //Length of each interval 
	int time_intervals; //Number of intervals
	float delta_time; //Length of each interval
	float time_boundary; //Total time
};

float* initialize_originals(Inputs);

Inputs get_inputs();

void diffusion(Inputs, float*);

