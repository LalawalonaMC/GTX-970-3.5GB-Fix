#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>
#include <vector>
#include <cstring>

// The target limit: 3.5GB, 375.. is around 3.5gb in bytes..
const VkDeviceSize LIMIT_35GB = 3758096384ULL; 

// Intercept function
VKAPI_ATTR void VKAPI_CALL Hook_GetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties) 
{
    // 1. Get the actual properties from the driver
    // In a real layer, you'd use the dispatch table, but here's the logic:
    // im too lazy for a real implementation for now
    
    for (uint32_t i = 0; i < pMemoryProperties->memoryHeapCount; i++) {
        // If it's the main VRAM heap and it's 4GB
        if ((pMemoryProperties->memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) &&
            (pMemoryProperties->memoryHeaps[i].size > LIMIT_35GB)) {
            
            // Force it to 3.5GB
            pMemoryProperties->memoryHeaps[i].size = LIMIT_35GB;
        }
    }
}
