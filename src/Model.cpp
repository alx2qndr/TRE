#include "Model.hpp"

#include <cassert>
#include <cstring>

namespace tre {

Model::Model(Device& device, const std::vector<Vertex>& vertices)
    : device { device }
{
    createVertexBuffers(vertices);
}

Model::~Model()
{
    vkDestroyBuffer(device.logicalDevice, vertexBuffer, nullptr);
    vkFreeMemory(device.logicalDevice, vertexBufferMemory, nullptr);
}

void Model::createVertexBuffers(const std::vector<Vertex>& vertices)
{
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "Vertex count must be at least 3");
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
    device.createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        vertexBuffer,
        vertexBufferMemory);

    void* data;
    vkMapMemory(device.logicalDevice, vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(device.logicalDevice, vertexBufferMemory);
}

void Model::draw(VkCommandBuffer commandBuffer)
{
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void Model::bind(VkCommandBuffer commandBuffer)
{
    VkBuffer buffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

} // namespace tre