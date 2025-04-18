#include "Application.hpp"

#include <array>
#include <cassert>
#include <stdexcept>

namespace tre {
struct SimplePushConstantData {
    alignas(32) glm::mat2 transform = { 1.0f };
    alignas(16) glm::vec2 offset;
    alignas(16) glm::vec3 color;
};

Application::Application()
{
    loadObjects();
    createPipelineLayout();
    createPipeline();
}

Application::~Application()
{
    vkDestroyPipelineLayout(device.logicalDevice, pipelineLayout, nullptr);
}

void Application::run()
{
    while (!window.shouldClose()) {
        glfwPollEvents();

        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapchainRenderPass(commandBuffer);
            renderObjects(commandBuffer);
            renderer.endSwapchainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.logicalDevice);
}

void Application::loadObjects()
{
    std::vector<Vertex> vertices {
        { { 0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } }
    };
    auto model = std::make_shared<Model>(device, vertices);

    auto triangle = Object::create();
    triangle.model = model;
    triangle.color = { 1.0f, 0.0f, 0.0f };
    triangle.transform2D.translation.x = 0.0f;
    triangle.transform2D.scale = { 2.0f, 0.5f };
    triangle.transform2D.rotation = { 0.25f * glm::two_pi<float>() };

    objects.push_back(std::move(triangle));
}

void Application::createPipelineLayout()
{
    VkPushConstantRange pushConstantRange = {};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstantData);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(device.logicalDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void Application::createPipeline()
{
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig {};
    Pipeline::defaultPipelineConfigInfo(pipelineConfig);

    pipelineConfig.renderPass = renderer.getSwapchainRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;

    pipeline = std::make_unique<Pipeline>(
        device,
        "../assets/shaders/bin/default.vert.spv",
        "../assets/shaders/bin/default.frag.spv",
        pipelineConfig);
}

void Application::renderObjects(VkCommandBuffer commandBuffer)
{
    pipeline->bind(commandBuffer);

    for (auto& obj : objects) {
        obj.transform2D.rotation = glm::mod(obj.transform2D.rotation + 0.01f, glm::two_pi<float>());
        SimplePushConstantData push = {};
        push.offset = obj.transform2D.translation;
        push.color = obj.color;
        push.transform = obj.transform2D.mat2();

        vkCmdPushConstants(
            commandBuffer,
            pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(SimplePushConstantData),
            &push);

        obj.model->bind(commandBuffer);
        obj.model->draw(commandBuffer);
    }
}
} // namespace tre
