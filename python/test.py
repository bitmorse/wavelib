import ctypes
import numpy as np

# Load the shared library
lib = ctypes.CDLL('./libwavelibwrapper.so')

# Define the argument types for the call_cwt function
lib.call_cwt.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS'),  # signal
    ctypes.c_float,  # param
    ctypes.c_int,    # N
    ctypes.c_float,  # dt
    ctypes.c_int     # J
]

# Define the return type for the call_cwt function
lib.call_cwt.restype = None

# Create an example signal (replace this with your actual signal)
N = 1024  # Length of your signal
signal = np.random.rand(N).astype(np.double)  # Example signal

# Parameters for call_cwt (replace these with your actual parameters)
param = 6.0
dt = 0.1
J = 20

# Call the function
cwt_magnitude = lib.call_cwt(signal, param, N, dt, J)
