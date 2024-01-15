1. Add ´set(CMAKE_POSITION_INDEPENDENT_CODE ON)´ to the top AFTER "project(...." of the CMakeLists.txt file in the root folder.


2. Compile the main library first, in the root folder using the following commands:
```
cmake .
make
```

3. Compile the python wrapper using the following commands:
```
cd python
make
```

4. Run the python script to test the library:
```
python test.py
```



On Apple Silicon, you may need to set the env var CMAKE_HOST_SYSTEM_PROCESSOR to arm64.
