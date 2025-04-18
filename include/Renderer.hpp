#pragma once

#include <memory>
#include <vector>
#include <cassert>

#include <vulkan/vulkan.h>

#include "Context.hpp"
#include "Device.hpp"
#include "Swapchain.hpp"
#include "Window.hpp"

namespace tre {
class Renderer {
public:
    Renderer(Context& contextRef, Device& deviceRef, Window& windowRef);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    VkRenderPass getSwapchainRenderPass() const { return swapchain->getRenderPass(); }

    bool isFrameInProgress() const { frameStarted; }

    VkCommandBuffer getCurrentCommandBuffer() const
    {
        assert(frameStarted && "Cannot get command buffer when frame not in progress!");
        return commandBuffers[currentFrameIndex];
    }

    VkCommandBuffer beginFrame();
    void endFrame();

    void beginSwapchainRenderPass(VkCommandBuffer commandBuffer);
    void endSwapchainRenderPass(VkCommandBuffer commandBuffer);

private:
    void createCommandBuffers();
    void freeCommandBuffers();
    void recreateSwapchain();

    Context& context;
    Device& device;
    Window& window;

    std::unique_ptr<Swapchain> swapchain;
    std::vector<VkCommandBuffer> commandBuffers;

    uint32_t currentFrameIndex;
    bool frameStarted = false;
};
} // namespace tre
