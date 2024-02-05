#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders/shader.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float mixPercentage = 0.0f;
float angle = 0.0f;

unsigned int load_texture(const char* texturePath, bool isPNG = false) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isPNG ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return texture;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bruno Luiz Dias Alves de Castro", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader myShader("shaders/circleShader.vs", "shaders/circleShader.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    unsigned int tex_background = load_texture("textures/background.jpg");
    unsigned int tex_ball = load_texture("textures/ball.png", true);

    float vertices[] = {
        // first hexagon        // colors           // texture coords
         -0.05f,  0.15f, 0.0f,  1.0f, 0.0f, 0.0f,   4.0f, 1.0f,
         -0.90f,  0.15f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
         -0.45f, -0.10f, 0.0f,  0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
         -0.05f,  0.65f, 0.0f,  1.0f, 1.0f, 0.0f,   4.0f, 3.0f,
         -0.90f,  0.65f, 0.0f,  0.0f, 1.0f, 1.0f,   0.0f, 3.0f,
         -0.45f,  0.90f, 0.0f,  1.0f, 0.0f, 1.0f,   2.0f, 4.0f,

        // second hexagon       // colors           // texture coords
          0.05f,  0.15f, 0.0f,  1.0f, 0.0f, 0.0f,   4.0f, 1.0f,
          0.90f,  0.15f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
          0.45f, -0.10f, 0.0f,  0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
          0.05f,  0.65f, 0.0f,  1.0f, 1.0f, 0.0f,   4.0f, 3.0f,
          0.90f,  0.65f, 0.0f,  0.0f, 1.0f, 1.0f,   0.0f, 3.0f,
          0.45f,  0.90f, 0.0f,  1.0f, 0.0f, 1.0f,   2.0f, 4.0f,

        // third hexagon        // colors           // texture coords
         -0.40f, -0.20f, 0.0f,  1.0f, 0.0f, 0.0f,   4.0f, 1.0f,
          0.40f, -0.20f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
          0.00f,  0.05f, 0.0f,  0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
         -0.40f, -0.70f, 0.0f,  1.0f, 1.0f, 0.0f,   4.0f, 3.0f,
          0.40f, -0.70f, 0.0f,  0.0f, 1.0f, 1.0f,   0.0f, 3.0f,
          0.00f, -0.90f, 0.0f,  1.0f, 0.0f, 1.0f,   2.0f, 4.0f,
    };

    unsigned int indices[] = {
        // first hexagon
        0, 1, 2,
        0, 1, 3,
        1, 4, 3,
        3, 4, 5,

        // second hexagon
        6, 7, 8,
        6, 7, 9,
        7, 10, 9,
        9, 10, 11,

        // third hexagon
        12, 13, 14,
        12, 13, 15,
        13, 15, 16,
        15, 16, 17
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // copy the indices array in a buffer for OpenGL to use

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3
    * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6
    * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

    // glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    myShader.use();

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex_background);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex_ball);

        myShader.setFloat("mixValue", mixPercentage);
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);
        myShader.setFloat("angle", angle);

        myShader.setInt("hexagon", 0);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        myShader.setInt("hexagon", 1);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));

        myShader.setInt("hexagon", 2);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        mixPercentage += 0.01f;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        mixPercentage -= 0.01f;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        angle -= 0.01f;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        angle += 0.01f;

    if (mixPercentage > 1.0f) mixPercentage = 1.0f;
    if (mixPercentage < 0.0f) mixPercentage = 0.0f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}