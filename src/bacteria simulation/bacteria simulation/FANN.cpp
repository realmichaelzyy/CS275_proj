#include <stdio.h>
#include <string>
#include "FANN.h"
#include <random>
#include <time.h>
#include <utility>
#include <iostream>
using namespace std;

void FANN_Train(string datafile, string netfile) 
{
    const unsigned int num_input = 31;
    const unsigned int num_output = 2;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 5;
    const float desired_error = (const float) 0.001;

    const unsigned int max_epochs = 1000;
    const unsigned int epochs_between_reports = 100;

    struct fann *ann = fann_create_standard(num_layers, num_input,
        num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, datafile.c_str(), max_epochs,
        epochs_between_reports, desired_error);

    fann_save(ann, netfile.c_str());

    fann_destroy(ann);
}

void FANN_Test(string netfile, fann_type* input, double& dirX, double& dirY)
{
    struct fann *ann = fann_create_from_file(netfile.c_str());

    fann_type *calc_out; 
    calc_out = fann_run(ann, input);
    dirX = (double) calc_out[0];
    dirY = (double) calc_out[1];
    fann_destroy(ann);
    // pair<double, double> ret;
    // ret.first = calc_out[0];
    // ret.second = calc_out[1];
    // return ret;
}


// int main()
// {
//     FANN_Train("test.txt", "training.net");
//     // fann_type* input = new fann_type[2];
//     // input[0] = -1;
//     // input[1] = 1;
//     // fann_type *result = FANN_Test("training.net", input);
//     // printf("xor test (%f,%f) -> %f\n", input[0], input[1], result[0]);
//     return 0;
// }
