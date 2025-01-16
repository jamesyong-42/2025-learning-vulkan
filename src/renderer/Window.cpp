#include "Window.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>
namespace vge {
    Window::Window(int width, int height, std::string name) : WIDTH(width), HEIGHT(height), windowName(name) {
        initWindow();
        std::cout<<"Window created"<<std::endl;
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // not to create opengl context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);
    }
    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
}