#pragma once
#include "Device.hpp"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace vge {
    class Model {
    public:
        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        Model(Device &device, const std::vector<Vertex> &vertices);

        ~Model();

        Model(const Model &) = delete;

        Model &operator=(const Model &) = delete;

        void bind(VkCommandBuffer cmd);

        void draw(VkCommandBuffer cmd);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

        Device &device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}