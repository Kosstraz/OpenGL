#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define W_FLOAT 0
#define W_DOUBLE 1
#define W_INT 2
#define W_UINT 3
#define W_FLOATV 4

Window::Window()
{}

void Window::BackgroundColor(float r, float g, float b, float a)
{
    if (r > 1.0f and g > 1.0f and b > 1.0f)
    {
        r /= 255; g /= 255; b /= 255;
    }
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::GetInput(GLFWwindow* window, int key, int action, bool infoLog)
{
    if (glfwGetKey(window, key) == action)
    {
        if (infoLog)
        {
            std::cout << key << " - " << action << std::endl;
        }
        return true;
    }
}

void Window::CloseWindow(GLFWwindow* window, int key)
{
    if (GetInput(window, key, 1, false))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int Window::OpenWindow(GLFWwindow* window, const char* windowName)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(800, 600, windowName, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "ERROR::WINDOW::CREATION" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD::INITIALISATION" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        //all inputs
        CloseWindow(window, GLFW_KEY_ESCAPE);

        //all rendering commands
        BackgroundColor(44.0f, 176.0f, 245.0f, 1.0f);
        BuildTriangle(window);//"1.0f", "0.5f", "0.2f"

            //check and call events, and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Window::BuildTriangle(GLFWwindow* window)
{

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,               // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,               // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,               // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f                // top left 
    };
    unsigned int indices[] = {  // Notons que l’on commence à 0!
    0, 1, 3,   // premier triangle
    1, 2, 3    // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      // Colle les triangles entres-eux
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(VAO);

    Shaders shader("VertexShaderSource.vert", "FragmentShaderSource.frag");
    Texture tex;

    shader.use();
    
    //tex.additiveTextures("textures/W_grass512x512.png", "textures/destroy_2 512x512.png");
    tex.addTexture("textures/W_grass512x512.png", false);
    shader.setUniform("texture1Offset", W_FLOAT, 2, 0.0f, 0.0f);
    shader.setUniform("texture2Offset", W_FLOAT, 2, 0.0f, 0.0f);
    shader.setFloat("opacity", 0.4f);
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    float timeValue = glfwGetTime();

    const float w = 1.0f;
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 transform(w);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
    transform = glm::rotate(transform, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
    vec = transform * vec;
    shader.setMatrix("transform", 4, 1, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    float sinusMove = (sin(glfwGetTime()) / 2.0f) + 0.5f;
    glm::mat4 trans(w);
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    trans = glm::scale(trans, glm::vec3(sinusMove, sinusMove, sinusMove));
    vec = trans * vec;
    shader.setMatrix("transform", 4, 1, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::mat4 tr(w);
    tr = glm::translate(tr, glm::vec3(0.0f, sinusMove, 0.0f));
    tr = glm::scale(tr, glm::vec3(0.2f, 0.2f, 0.2f));
    shader.setMatrix("transform", 4, 1, glm::value_ptr(tr));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

}

Window::~Window()
{}