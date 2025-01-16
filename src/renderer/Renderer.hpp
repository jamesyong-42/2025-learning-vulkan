#pragma once

#include "renderer/Window.hpp"
#include "renderer/Device.hpp"
#include "renderer/SwapChain.hpp"
//std
#include <memory>
#include <vector>
#include <cassert>

namespace vge {
    class Renderer {
    public:
        Renderer(Window &window, Device &device);

        ~Renderer();

        Renderer(const Renderer &) = delete;

        Renderer &operator=(const Renderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const {
            return swapChain->getRenderPass();
        }

        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "cannot get current command buffer when frame is not started");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "cannot get frame index when frame is not started");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();

        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();

        void freeCommandBuffers();

        void recreateSwapChain();

        Window &window;
        Device &device;
        std::unique_ptr<SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
    };
}
