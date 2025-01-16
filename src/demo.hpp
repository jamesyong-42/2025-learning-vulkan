#pragma once

#include "renderer/Window.hpp"
#include "renderer/Pipeline.hpp"
#include "renderer/Device.hpp"
#include "renderer/SwapChain.hpp"
#include "renderer/Model.hpp"
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
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
        Window window{WIDTH, HEIGHT, "Demo"};
        Device device{window};
        std::unique_ptr<SwapChain> swapChain;
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<Model> model;
    };
}
