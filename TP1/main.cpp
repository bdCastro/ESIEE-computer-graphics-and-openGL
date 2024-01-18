#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Bruno Luiz Dias Alves de Castro", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // blue background
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // check if the user pressed the 'E' key
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            // exit program
            glfwSetWindowShouldClose(window, true);
        }
    }

    glfwTerminate();
    return 0;
}