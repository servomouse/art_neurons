#include <iostream>
#include <cmath>

class neuron
{
    double **inputs;
    double *_inputs;
    double *weight;
    double *delta_weight;
    double b;
    double delta_b;
    double output = 0;
    double z = 0;
    int input_width;
    double error = 0;

    public:
    neuron(int inputs_num, double * _weights, double _bias)
    {
        input_width = inputs_num;
        inputs = new double*[inputs_num];
        _inputs = new double[inputs_num];
        weight = new double[inputs_num];
        delta_weight = new double[inputs_num];
        for(int i=0; i<inputs_num; i++)
            weight[i] = _weights[i];
        b = _bias;
    }

    ~neuron(void)
    {
        delete[] inputs;
        delete[] _inputs;
        delete[] weight;
        delete[] delta_weight;
    }

    void set_input(int index, double *i)
    {
        inputs[index] = i;
    }

    double get_weight(int index)
    {
        return weight[index];
    }

    void set_weight(int index, double w)
    {
        weight[index] = w;
    }

    void set_bias(double bias)
    {
        b = bias;
    }

    void calc_output(void)
    {
        z = b;
        for(int i=0; i<input_width; i++)
        {
            _inputs[i] = *(inputs[i]);
            z += _inputs[i] * weight[i];
        }
        output = tanh(z);
    }

    double get_activation(void)
    {
        return z;
    }

    /* returns a pointer to the output value */
    double * get_output(void)
    {
        return &output;
    }

    void set_error(double e)
    {
        error = e * (1 - pow(tanh(z), 2.0));
        delta_b = error;
        for(int i=0; i<input_width; i++)
        {
            delta_weight[i] = _inputs[i] * error;
        }
    }

    void update_weights(double coefficient)
    {
        for(int i=0; i<input_width; i++)
        {
            weight[i] += coefficient * delta_weight[i];
        }
        b += delta_b;
    }
};

int main(void)
{
    double weights[] = {1, 1, 1, 1};
    double inputs[] = {1, 1, 1, 1};
    neuron n = neuron(1, weights, 1.0);
    n.set_input(0, &inputs[0]);
    double *out = n.get_output();
    for(int i=0; i<100; i++)
    {  
        n.calc_output();
        n.set_error(-0.33 - *out);
        n.update_weights(0.1);
        std::cout << "Output value: " << *out << std::endl;
    }
    

    return 0;
}