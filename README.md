# Simple robot simulator in C++

Compile+run with g++ (with multi-threading):

```g++ src/robot.cpp -o rob_test.exe -fopenmp && ./rob_test.exe```

(omit the -fopenmp flag to disable multi-threading. I had issues using openmp with clang...)


On linux, to use openGL for rendering compile via 

```g++ src/viz.cpp src/robot.cpp src/glad.c -o viz_test.exe -ldl -lglfw -lGL```