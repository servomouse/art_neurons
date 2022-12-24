#include <iostream>
#include <cmath>

class neuron
{
    double **inputs;
    double *weight;
    double bias;
    double output = 0;
    double z = 0;
    int input_width;

    public:
    neuron(int inputs_num, double * _weights, double _bias)
    {
        input_width = inputs_num;
        inputs = new double*[inputs_num];
        weight = new double[inputs_num];
        for(int i=0; i<inputs_num; i++)
            weight[i] = _weights[i];
        bias = _bias;
    }

    ~neuron(void)
    {
        delete[] inputs;
        delete[] weight;
    }

    void set_input(int index, double *input)
    {
        inputs[index] = input;
    }

    void calc_output(void)
    {
        z = bias;
        for(int i=0; i<input_width; i++)
            z += *(inputs[i]) * weight[i];
        output = tanh(z);
    }

    /* returns a pointer to the output value */
    double * get_output(void)
    {
        return &output;
    }

};

int main(void)
{
    double weights[] = {1, 1, 1, 1};
    double inputs[] = {1, 1, 1, 1};
    neuron n = neuron(1, weights, 1.0);
    n.set_input(0, &inputs[0]);
    double *out = n.get_output();
    n.calc_output();
    
    std::cout << "Hello world!\n" << *out << std::endl;

    return 0;
}