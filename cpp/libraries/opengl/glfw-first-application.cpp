#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>

int main()
{
    int windowWidth = 640;
    int windowHeight = 480;

    if (!glfwInit()) {
        return -1;
    }

    if (GL_TRUE != glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 16, 0, GLFW_WINDOW)) {
        std::cerr << "Unable to create window" << std::endl;
        return -1;
    }

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_REFRESH_RATE, 60);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glfwSwapInterval(1);

    bool running = true;
    glViewport(0, 0, windowWidth, windowHeight);

    while (running)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers();
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    glfwTerminate();
    return 0;
}