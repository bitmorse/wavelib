import ctypes
import numpy as np

class WavelibH:
    def __init__(self, lib_path):
        # Load the shared library
        self.lib = ctypes.CDLL(lib_path)

        # Define the argument types for the call_cwt function
        self.lib.call_cwt.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS'),  # signal
            ctypes.c_float,  # param
            ctypes.c_int,    # N
            ctypes.c_float,  # dt
            ctypes.c_int     # J
        ]

        # Define the return type for the call_cwt function
        self.lib.call_cwt.restype = None
        
    def cwt(self, signal, param, dt, J):
        N = len(signal)
        # Ensure the signal is a numpy array with dtype np.double
        signal = np.array(signal, dtype=np.double)

        # Allocate memory for the real and imaginary parts of the output
        real_output = np.empty(N * J, dtype=np.double)
        imag_output = np.empty(N * J, dtype=np.double)

        # Adjust the argtypes for the modified function
        self.lib.call_cwt.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS'),
            ctypes.c_float,
            ctypes.c_int,
            ctypes.c_float,
            ctypes.c_int,
            np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS'),
            np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS')
        ]

        # Call the C function
        self.lib.call_cwt(signal, param, N, dt, J, real_output, imag_output)
        
        #reshape outputs
        real_output = real_output.reshape((J, N))
        imag_output = imag_output.reshape((J, N))

        # Return the real and imaginary parts
        return real_output, imag_output
    
    
if __name__ == '__main__':
    #random input signal, N = 200, dt = 1, J = 10, param = 5
    signal = np.random.rand(200)
    param = 5
    dt = 1
    J = 10
    
    wvt = WavelibH('./libwavelibwrapper.so')    
    re, im = wvt.cwt(signal, param, dt, J)
    
    print(re.shape)
    print(im.shape)
    
    magnitude = np.sqrt(re**2 + im**2)
    print(magnitude)