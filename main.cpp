#include "main.hpp"

int main(){
	Inputs inputs = get_inputs();
	float *original = initialize_originals(inputs);
	diffusion(inputs, original);
	return 0;
}

Inputs get_inputs(){
	float a, b, c, d, e, f, g, h;
	Inputs inputs;
	ifstream heat_input ("heat_input.dat");
	while (heat_input >> a >> b >> c >> d >> e >> f >> g >> h){
		inputs.thermal_conductivity = a;
		inputs.density = b;
		inputs.specific_heat = c;
		inputs.initial_temp = d;
		inputs.length = e;
		inputs.position_intervals = f;
		inputs.delta_x = inputs.length/inputs.position_intervals;
		inputs.time_intervals = g;
		inputs.delta_time = h;
		inputs.time_boundary = inputs.time_intervals * inputs.delta_time;	}
	return inputs;
}

float* initialize_originals(Inputs inputs){
	float k = 0.0;
	float *original = new float[inputs.position_intervals];
	original[0] = inputs.initial_temp;
	for(int j = 1; j<inputs.position_intervals; j++){
		original[j] = 0;
	}
	return original;
}


void diffusion(Inputs inputs, float* original){
	ofstream heat_bin ("heat_bin.dat", ios::binary);
	float time, position, first_temp = inputs.initial_temp, second_temp = 0, third_temp = 0, new_temp = 0;
	float *temperatures = new float[inputs.position_intervals];
	for(time = 0; time<inputs.time_boundary; time+=inputs.delta_time){
		cout<<"Time: "<<time<<" seconds"<<endl;
		for(int j = 0; j<inputs.position_intervals; j++)
			temperatures[j] = original[j];
		for (int i = 1; i<inputs.position_intervals-1; i++){	
			new_temp = ((inputs.thermal_conductivity*inputs.delta_time)/(inputs.density*inputs.specific_heat*pow(inputs.delta_x, 2)))*(temperatures[i+1]-2*(temperatures[i])+temperatures[i-1])+temperatures[i];
			original[i] = new_temp;
			printf("%.2f", original[i]);
			cout<<"  ";
		}
		heat_bin.write((char*)original, sizeof(float)*inputs.position_intervals);
		cout<<endl<<endl;
	}
	heat_bin.close();
}
