#include "demo.hpp"
#include "renderer/Camera.hpp"
#include "game/KeyboardMovementController.hpp"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <chrono>
#include <iostream>
#include <ostream>
#include <stdexcept>

#define MAX_FRAME_TIME 10.f

namespace vge {
    Demo::Demo() {
        loadGameObjects();
    }

    Demo::~Demo() {
    }


    void Demo::run() {
        SimpleRenderSystem simpleRenderSystem{device, renderer.getSwapChainRenderPass()};
        Camera camera{};
        // camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
        // camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!window.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspectRatio = renderer.getAspectRatio();
            // camera.setOrthographicProjection(-aspectRatio, aspectRatio, -1, 1, -1, 1);
            camera.setPerspectiveProjection(glm::radians(50.f), aspectRatio, 0.1f, 10.f);

            if (auto commandBuffer = renderer.beginFrame()) {
                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(device.device());
    }

    void Demo::loadGameObjects() {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "models/smooth_vase.obj");
        auto gameObject = GameObject::createGameObject();
        gameObject.model = model;
        gameObject.transform.translation = {0.f, 0.f, 2.5f};
        gameObject.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(gameObject));
    }
}
