#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include <vulkan/vulkan.h>

#include "Window.hpp"

namespace tre {
class Context {
public:
    Context(const std::string& applicationNameRef, Window& windowRef);
    ~Context();

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif 

    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void checkRequiredInstanceExtensions();
    std::vector<const char*> getRequiredExtensions();
    bool isValidationLayerSupport();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    Window& window;
    const std::string& applicationName;

};
}