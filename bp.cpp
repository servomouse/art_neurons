#include <cmath>

struct network
{
    uint inputs;         // number of inputs
    uint depth;         // number of neurons
    double *weights;    // pointer to weights matrix
};

// double *m_forward(double *inputs, network net)
// {
//     /* returns the matrix of calculated values of neurons
//     it's usable for deep learning. */
//     uint net_size = net.inputs + net.depth;
//     double *retval[2] = {new double[net_size], new double[net_size]};
//     double *a = retval[0];   // outputs
//     double *z = retval[1];   // weighted inputs
//     for(uint i=0; i<net.inputs; i++) // copy inputs values to a and z
//         a[i] = z[i] = inputs[i];

//     for(uint i=0; i<net_size; i++)
//     {
//         double temp = 0;
//         for(uint j=0; j<net_size; j++)
//         {
//             if(j == i)
//                 temp += net.weights[i * net.inputs + j * net.depth];
//             else
//                 temp += net.weights[i * net.inputs + j * net.depth] * a[j];
//         }
//         z[i] += temp;
//         a[i] += tanh(temp);
//     }
//     for layer in range(len(w)):  // layer
//         d = []
//         d_z = []
//         for i in range(len(w[layer])):  // neuron
//             s = 0
//             for j in range(len(w[layer][i])):  // weight
//                 s += a[layer][j] * w[layer][i][j]
//             d.append(math.tanh(s + b[layer][i]))
//             d_z.append(s + b[layer][i])
//         a.append(d)
//         z.append(d_z)
//     return a, z
// }


// def m_backward(w, a, y, z):
//     /* backward propagation. [a] is activations, [y] is targets, [z] is sums.
//     Returns two matrix of deltas: for weights and for biases */
//     r_w = copy.deepcopy(w)
//     r_w.reverse()
//     r_a = copy.deepcopy(a)
//     r_a.reverse()
//     e = [[((a[-1][i] - y[i]) * (1 - a[-1][i] ** 2)) for i in range(len(y))]]
//     for layer in range(len(r_w) - 1):
//         d = []
//         for i in range(len(r_a[layer + 1])):
//             s = 0
//             for j in range(len(r_w[layer])):
//                 s += e[layer][j] * r_w[layer][j][i]
//             d.append(s * (1 - (r_a[layer + 1][i] ** 2)))
//         e.append(d)
//     r_e = copy.deepcopy(e)
//     r_e.reverse()

//     e_w = []
//     for layer in range(len(w)):
//         s = []
//         for i in range(len(w[layer])):
//             n = []
//             for j in range(len(w[layer][i])):
//                 n.append(r_e[layer][i] * z[layer][j])
//             s.append(n)
//         e_w.append(s)
//     return r_e, e_w


// def m_update(w, b, r_e, e_w):
//     /* updates weights and biases in the network  */
//     for layer in range(len(w)):
//         for i in range(len(w[layer])):
//             for j in range(len(w[layer][i])):
//                 w[layer][i][j] -= e_w[layer][i][j]
//     for layer in range(len(b)):
//         for i in range(len(b[layer])):
//             b[layer][i] -= r_e[layer][i] * 0.001


// def m_get_result(inputs, network):
//     /* get network output(s) for data sample  */
//     return m_forward(inputs, network['weights'], network['biases'])[0][-1]


// void m_train(network: dict, dataset: list[dict]):
//     /* data is a list of dicts like [{'inputs': list[float], 'target': float}, ...]
//     'target' is the expected output for the network */
//     w = network['weights']
//     b = network['biases']
//     w_deltas = [[[0.0 for _ in range(len(w[layer][i]))] for i in range(len(w[layer]))] for layer in range(len(w))]
//     b_deltas = [[0.0 for _ in range(len(b[i]))] for i in range(len(b))]
//     for sample in dataset:
//         a, z = m_forward(sample['inputs'], network['weights'], network['biases'])
//         delta_b, delta_w = m_backward(network['weights'], a, sample['target'], z)
//         for layer in range(len(w)):
//             for i in range(len(w[layer])):
//                 for j in range(len(w[layer][i])):
//                     w_deltas[layer][i][j] += delta_w[layer][i][j]
//         for i in range(len(b)):
//             for j in range(len(b[i])):
//                 b_deltas[i][j] += delta_b[i][j]

//     for layer in range(len(w)):
//         for i in range(len(w[layer])):
//             for j in range(len(w[layer][i])):
//                 w_deltas[layer][i][j] /= len(dataset)
//     for i in range(len(b)):
//         for j in range(len(b[i])):
//             b_deltas[i][j] /= len(dataset)
//     m_update(network['weights'], network['biases'], b_deltas, w_deltas)