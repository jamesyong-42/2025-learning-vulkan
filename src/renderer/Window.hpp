#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace vge {
    class Window {
    public:
        Window(int width, int height, std::string name);

        ~Window();

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        bool shouldClose() const { return glfwWindowShouldClose(window); };

        VkExtent2D getExtent() { return {static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        void initWindow();

        const int WIDTH;
        const int HEIGHT;
        std::string windowName;
        GLFWwindow *window;
    };
}
