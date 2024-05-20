#include "robot.hpp"



__global__ void compute_spring_forces_kernel(float* masses, float* springs, int total_masses, int total_springs, float t) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < total_springs) {
        // Compute spring forces for spring i
        //TODO: implement kernel
    }
}

void Robot::compute_spring_forces(float t) {
    float* d_masses, *d_springs;
    cudaMalloc(&d_masses, total_masses * 15 * sizeof(float));
    cudaMalloc(&d_springs, total_springs * 6 * sizeof(float));

    cudaMemcpy(d_masses, masses.data(), total_masses * 15 * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_springs, springs.data(), total_springs * 6 * sizeof(float), cudaMemcpyHostToDevice);

    int threads_per_block = 256;
    int blocks_per_grid = (total_springs + threads_per_block - 1) / threads_per_block;

    compute_spring_forces_kernel<<<blocks_per_grid, threads_per_block>>>(d_masses, d_springs, total_masses, total_springs, t);

    cudaMemcpy(masses.data(), d_masses, total_masses * 15 * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_masses);
    cudaFree(d_springs);
}