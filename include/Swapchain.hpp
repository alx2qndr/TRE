#pragma once

#include <memory>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "Context.hpp"
#include "Device.hpp"

namespace tre {
class Swapchain {
public:
    Swapchain(Context& contextRef, Device& deviceRef, VkExtent2D windowExtent);
    Swapchain(Context& contextRef, Device& deviceRef, VkExtent2D windowExtent, std::shared_ptr<Swapchain> previous);

    ~Swapchain();

    Swapchain(const Swapchain&) = delete;
    Swapchain& operator=(const Swapchain&) = delete;

    VkFramebuffer getFrameBuffer(int index) const { return swapchainFramebuffers[index]; }
    VkRenderPass getRenderPass() const { return renderPass; }
    VkImageView getImageView(int index) const { return swapchainImageViews[index]; }
    size_t imageCount() const { return swapchainImages.size(); }
    VkFormat getSwapchainImageFormat() const { return swapchainImageFormat; }
    VkExtent2D getSwapchainExtent() const { return swapchainExtent; }
    uint32_t width() const { return swapchainExtent.width; }
    uint32_t height() const { return swapchainExtent.height; }

    float extentAspectRatio() const
    {
        return static_cast<float>(swapchainExtent.width) / static_cast<float>(swapchainExtent.height);
    }
    VkFormat findDepthFormat();

    VkResult acquireNextImage(uint32_t* imageIndex);
    VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    bool compareFormats(const Swapchain& swapchain) const
    {
        return swapchain.swapchainDepthFormat == swapchainDepthFormat
            && swapchain.swapchainImageFormat == swapchainImageFormat;
    }

private:
    void init();
    void createSwapchain();
    void createImageViews();
    void createDepthResources();
    void createRenderPass();
    void createFramebuffers();
    void createSyncObjects();

    VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VkFormat swapchainImageFormat;
    VkFormat swapchainDepthFormat;
    VkExtent2D swapchainExtent;

    std::vector<VkFramebuffer> swapchainFramebuffers;
    VkRenderPass renderPass;

    std::vector<VkImage> depthImages;
    std::vector<VkDeviceMemory> depthImageMemorys;
    std::vector<VkImageView> depthImageViews;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;

    Context& context;
    Device& device;
    VkExtent2D windowExtent;

    VkSwapchainKHR swapchain;
    std::shared_ptr<Swapchain> oldSwapchain;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;
};
} // namespace tre
