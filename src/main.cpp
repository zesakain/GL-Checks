#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"

int main() {
    // Initializing GLFW
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Arch Renderer", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    // Enable Depth Testing to make sure objects in front cover objects in back
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    // Define a simple Cube (only 1 face here for brevity)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f
    };

    // VBO: Vertex Buffer Object (stores data on GPU)
    // VAO: Vertex Array Object (stores how to read that data)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell GPU how to interpret the vertex data (3 floats per position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // --- MATH ZONE: TRANSFORMATION MATRICES ---

        // 1. Model Matrix: Rotate the object over time
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        // 2. View Matrix: Move the "Camera" back by 3 units
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // 3. Projection Matrix: Perspective (FOV, Aspect Ratio, Near, Far)
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Pass matrices to the shader
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        // Draw the object
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
