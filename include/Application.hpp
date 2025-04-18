#pragma once

#include <memory>
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Context.hpp"
#include "Device.hpp"
#include "Model.hpp"
#include "Object.hpp"
#include "Pipeline.hpp"
#include "Renderer.hpp"
#include "Swapchain.hpp"
#include "Window.hpp"

namespace tre {
class Application {
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void loadObjects();
    void createPipelineLayout();
    void createPipeline();
    void renderObjects(VkCommandBuffer commandBuffer);

    Window window { 640, 480, "Tiny Rendering Window" };
    Context context { "Tiny Rendering Application", window };
    Device device { context };
    Renderer renderer { context, device, window };
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<Object> objects;
};
} // namespace tre
