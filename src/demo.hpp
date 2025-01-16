#pragma once

#include "renderer/Window.hpp"
#include "renderer/Device.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/SimpleRenderSystem.hpp"
#include "game/GameObject.hpp"
//std
#include <memory>
#include <vector>
namespace vge {
    class Demo {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        Demo();
        ~Demo();
        Demo(const Demo&) = delete;
        Demo& operator=(const Demo&) = delete;

        void run();

    private:
        void loadGameObjects();

        Window window{WIDTH, HEIGHT, "Demo"};
        Device device{window};
        Renderer renderer{window, device};

        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<GameObject> gameObjects;
    };
}
