#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <eigen3/Eigen/Dense>
#include "robot.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using std::cout;
using std::endl;
using Eigen::Vector3f;

Robot robot; // Assuming you have an instance of your Robot class

void drawPoint(float x, float y, float z) {
    glColor3f(1.0, 2.0, 3.0);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void drawSpring(Vector3f p1, Vector3f p2) {
    glColor3f(-2.0, 1.0, 0.5);
    glBegin(GL_LINES);
    glVertex3f(p1.x(), p1.y(), p1.z());
    glVertex3f(p2.x(), p2.y(), p2.z());
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera and view transformations
    // ...
    glm::vec3 cameraPos(0.0f, 0.0f, 3.0f); // Position the camera at (0, 0, 3)
    glm::vec3 cameraFront(0.0f, 0.0f, -1.0f); // Camera is facing the negative z-axis
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Up vector is positive y-axis

    float fov = 45.0f; // Field of view in degrees
    float aspect = 800.0f / 600.0f; // Aspect ratio of the window
    float near = 0.1f; // Near clipping plane
    float far = 100.0f; // Far clipping plane

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);

    // Apply view and projection matrices
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&projection[0][0]); // Pass the pointer to the first element of the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&view[0][0]); // Pass the pointer to the first element of the matrix

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

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Robot Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // Set up OpenGL state
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Rendering loop
    // robot.compute_spring_forces(0.1);
    // robot.force_integration();

    // Rendering loop
    double lastTime = glfwGetTime();
    int frameCount = 0;
    // Render scene
    renderScene();

    while (!glfwWindowShouldClose(window)) {
        
        // Update simulation state
        // Calculate elapsed time
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();


         // Calculate and display frame rate
        frameCount++;
        if (currentTime - lastTime >= 1.0) {
            double fps = frameCount / (currentTime - lastTime);
            cout << "FPS: " << fps << endl;
            frameCount = 0;
            lastTime = currentTime;
        }
    }

    // Clean up
    glfwTerminate();
    return 0;
}
