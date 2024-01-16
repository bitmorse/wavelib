#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wavelib.h"

/*** 
Python version:
def bilinear_interpolate(cwt, target_shape):
    '''takes a wide cwt and transforms it to a square image by bilinear interpolation'''
    
    # Create a slightly larger shape for interpolation
    intermediate_shape = (target_shape[0] + 1, target_shape[1] + 1)
    new_cwt = np.zeros(intermediate_shape)
    old_shape = cwt.shape

    for i in range(intermediate_shape[0]):
        for j in range(intermediate_shape[1]):
            # Calculate the position in the original array
            x = (i * (old_shape[0] - 1)) / (intermediate_shape[0] - 1)
            y = (j * (old_shape[1] - 1)) / (intermediate_shape[1] - 1)

            x1 = int(x)
            y1 = int(y)
            x2 = min(x1 + 1, old_shape[0] - 1)
            y2 = min(y1 + 1, old_shape[1] - 1)

            # Calculate fractions
            wa = (x2 - x) * (y2 - y)
            wb = (x - x1) * (y2 - y)
            wc = (x2 - x) * (y - y1)
            wd = (x - x1) * (y - y1)

            # Linearly interpolate using the four nearest neighbors
            new_cwt[i][j] = wa * cwt[x1][y1] + wb * cwt[x2][y1] + wc * cwt[x1][y2] + wd * cwt[x2][y2]

    # Trim the last row and column
    return new_cwt[:target_shape[0], :target_shape[1]]
***/

//input_image (J rows, N columns) 
void call_bilinear_interpolate(double *input_image, double *input_image_interpolated, int N, int J, int new_width, int new_height) {
    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            // Adjusted calculations to ensure coordinates are within bounds
            double x = (i / (double)(new_width - 1)) * (N - 1);
            double y = (j / (double)(new_height - 1)) * (J - 1);

            int x1 = (int) x;
            int y1 = (int) y;
            int x2 = fmin(x1 + 1, N);
            int y2 = fmin(y1 + 1, J);

            double wa = (x2 - x) * (y2 - y);
            double wb = (x - x1) * (y2 - y);
            double wc = (x2 - x) * (y - y1);
            double wd = (x - x1) * (y - y1);

            int index = i * new_height + j;
            int input_index1 = x1 * J + y1;
            int input_index2 = x2 * J + y1;
            int input_index3 = x1 * J + y2;
            int input_index4 = x2 * J + y2;

            input_image_interpolated[index] = wa * input_image[input_index1] +
                                              wb * input_image[input_index2] +
                                              wc * input_image[input_index3] +
                                              wd * input_image[input_index4];
        }
    }
}

void call_cwt(double *signal, double *magnitude_output, int linear, float param, int N, float dt, int J) {
    const char *wave = "morl";  // Morlet wavelet
	const char *type = "pow";

    if (linear) {
        type = "lin";
    }

    cwt_object obj = cwt_init(wave, param, N, dt, J);
	strcpy(obj->type,type);


    // Perform the Continuous Wavelet Transform
    cwt(obj, signal);

    // Fill the output arrays with real and imaginary parts
    for (int j = 0; j < obj->J; j++) {
        for (int i = 0; i < N; i++) {
            int index = j * N + i;


            magnitude_output[index] = (sqrt(obj->output[index].re * obj->output[index].re +
                                      obj->output[index].im * obj->output[index].im));
        }
    }
}
