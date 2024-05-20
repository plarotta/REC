# Simple robot simulator in C++

Compile+run via 

```g++ src/robot.cpp -o rob_test.exe -fopenmp && ./rob_test.exe```

On linux, to use openGL for rendering compile via 

```g++ src/viz.cpp src/robot.cpp src/glad.c -o viz_test.exe -ldl -lglfw -lGL```