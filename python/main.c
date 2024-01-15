#include <stdio.h>
#include <math.h>
#include "wavelib.h"

void call_cwt(double *signal, float param, int N, float dt, int J, double *real_output, double *imag_output) {
    const char* wave = "morl";  // Morlet wavelet
    cwt_object obj = cwt_init(wave, param, N, dt, J);

    // Perform the Continuous Wavelet Transform
    cwt(obj, signal);

    // Fill the output arrays with real and imaginary parts
    for (int j = 0; j < obj->J; j++) {
        for (int i = 0; i < N; i++) {
            int index = j * N + i;
            real_output[index] = obj->output[index].re;
            imag_output[index] = obj->output[index].im;
        }
    }
}
