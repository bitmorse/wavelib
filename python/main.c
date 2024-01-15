#include <stdio.h>
#include <math.h>
#include "wavelib.h"

// This function can be called from Python
void call_cwt(double * signal, float param, int N, float dt, int J) {
    // Initialize the CWT object    
    const char* wave = "morl"; // Morlet wavelet
    cwt_object obj = cwt_init(wave, param, N, dt, J);

    printf("J: %i\n", obj->J);
    printf("dj: %f\n", obj->dj);
    printf("scale type: %s\n", obj->type);

    // Perform the Continuous Wavelet Transform
    cwt(obj, signal); 

    //printf("signal: \n");
    //for(int i = 0; i < SAMPLE_LENGTH; i++){
    //    printf("%f ", signal[i]);
    //}

    // Computing and printing the magnitude of the CWT output and the scales
    for (int j = 0; j < obj->J; j++) {  // Iterate over scales
        //printf("Scale %d: ", j);
        for (int i = 0; i < N; i++) {  // Iterate over signal length
            int index = j * N + i;  // Assuming output is a 1D array of size J * N
            double magnitude = sqrt(obj->output[index].re * obj->output[index].re +
                                    obj->output[index].im * obj->output[index].im);

            //PRINT DOUBLES
            printf("%lf ", magnitude);
        }
    }
}