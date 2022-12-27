#include <iostream>
#include <cmath>
#include <vector>

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

    double get_bias(void)
    {
        return b;
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

float random(float min, float max) //range : [min, max]
{
    static bool first = true;
    if (first) 
    {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
    }
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

/* Returns an array of randomly-generated weights for network initialisation */
double * get_weights(int number)
{
    double *arr = new double[number];   // don't forget to delete!
    for(int i=0; i<number; i++)
        arr[i] = random(-1, 1);
    return arr;
}

class network
{
    std::vector<std::vector<neuron>> brain;
    int inputs_num = 0;
    public:
    /* @arg: inputs - array of doubles used as inputs for the network
    *  @arg: args - simple line of integers describing how many neurons
    *  are in every layer. For example: 5, 5, 1 mean "create the network with
    *  2 layers of 5 neurons and with 1 neuront in the very last layer" */
    template<typename... Args>
    network(double * inputs, int inputs_width, Args... args)
    {
        std::vector<int> v;
        std::cout << sizeof...(args) << std::endl;
        auto b = [](std::vector<int> * v, int t){v->push_back(t);};
        (b(&v, args), ...);
        inputs_num = inputs_width;
        for(int i=0; i<v.size(); i++)
        {
            std::vector<neuron> layer;
            for(int n=0; n<v[i]; n++)
            {
                neuron n;
                double *w = NULL;
                if(0 == i)
                {
                    w = get_weights(inputs_num);
                    n = neuron(inputs_num, w, random(-1, 1));
                    for(j=0; j<inputs_num; j++)
                        n.set_input(j, &inputs[j]);
                    delete w;
                }
                else
                {
                    w = get_weights(v[i-1]);
                    n = neuron(v[i-1], w, random(-1, 1));
                    for(j=0; j<v[i-1]; j++)
                        n.set_input(j, brain[i-1][j].get_output());
                    delete w;
                }
                layer.push_back(n);
            }
            brain.push_back(layer);
        }
    }
};

int main(void)
{
    double weights[] = {1, 1, 1, 1};
    double inputs[] = {1, 1, 1, 1};
    network test = network(inputs, 4, 5, 5, 1);
    neuron n = neuron(1, weights, 1.0);
    n.set_input(0, &inputs[0]);
    double *out = n.get_output();
    double error;

    for(int i=0; i<10; i++)
    {
        inputs[0] =random(-1, 1);
        n.calc_output();
        n.set_error(sin(3.14159 * inputs[0]) - *out);
        n.update_weights(0.1);
        std::cout << "target = " << sin(3.14159 * inputs[0]) << ", output = " << *out << std::endl;
    }
    
    return 0;
}