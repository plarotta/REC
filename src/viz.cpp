#include <eigen3/Eigen/Dense>
#include "robot.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using Eigen::Vector3f;

Robot robot; // Assuming you have an instance of your Robot class

void drawPoint(float x, float y, float z) {
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void drawSpring(Vector3f p1, Vector3f p2) {
    glBegin(GL_LINES);
    glVertex3f(p1.x(), p1.y(), p1.z());
    glVertex3f(p2.x(), p2.y(), p2.z());
    glEnd();
}

Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye, const Eigen::Vector3f& center, const Eigen::Vector3f& up) {
    Eigen::Vector3f f = (center - eye).normalized();
    Eigen::Vector3f u = up.normalized();
    Eigen::Vector3f s = f.cross(u).normalized();
    u = s.cross(f);

    Eigen::Matrix4f mat = Eigen::Matrix4f::Identity();
    mat(0, 0) = s.x();
    mat(0, 1) = s.y();
    mat(0, 2) = s.z();
    mat(1, 0) = u.x();
    mat(1, 1) = u.y();
    mat(1, 2) = u.z();
    mat(2, 0) = -f.x();
    mat(2, 1) = -f.y();
    mat(2, 2) = -f.z();
    mat(0, 3) = -s.dot(eye);
    mat(1, 3) = -u.dot(eye);
    mat(2, 3) = f.dot(eye);

    return mat;
}

Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar) {
    float tanHalfFovy = tan(fovy / 2.0f);

    Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();
    mat(0, 0) = 1.0f / (aspect * tanHalfFovy);
    mat(1, 1) = 1.0f / tanHalfFovy;
    mat(2, 2) = -(zFar + zNear) / (zFar - zNear);
    mat(2, 3) = -1.0f;
    mat(3, 2) = -(2.0f * zFar * zNear) / (zFar - zNear);

    return mat;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera and view transformations
    Vector3f cameraPos(0.0f, 0.0f, 3.0f); // Position of the camera
    Vector3f cameraTarget(0.0f, 0.0f, 0.0f); // Point the camera is looking at
    Vector3f cameraUp(0.0f, 1.0f, 0.0f); // Up vector for the camera

    // Set up camera and view transformations
    Eigen::Matrix4f view = lookAt(cameraPos, cameraTarget, cameraUp);
    glLoadMatrixf(view.data());

    // Set up projection matrix
    Eigen::Matrix4f projection = perspective(45.0f * M_PI / 180.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.data());
    glMatrixMode(GL_MODELVIEW);

    // Draw point masses
    for (int i = 0; i < robot.total_masses; i++) {
        Vector3f pos = robot.masses.row(i).segment(0, 3).cast<float>();
        drawPoint(pos.x(), pos.y(), pos.z());
    }

    // Draw springs
    for (int i = 0; i < robot.total_springs; i++) {
        int m1_idx = robot.springs(i, 0);
        int m2_idx = robot.springs(i, 1);
        Vector3f p1 = robot.masses.row(m1_idx).segment(0, 3).cast<float>();
        Vector3f p2 = robot.masses.row(m2_idx).segment(0, 3).cast<float>();
        drawSpring(p1, p2);
    }
}

void idle() {
    // Update simulation state
    robot.compute_spring_forces(0);
    robot.force_integration();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// int main(int argc, char** argv) {
//     glfwInit(); // No need to pass argc and argv

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Robot Simulation", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//         // Load GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glClearColor(0.0, 0.0, 0.0, 1.0);
//     glEnable(GL_DEPTH_TEST);

//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);

//         display();

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return 0;
// }
