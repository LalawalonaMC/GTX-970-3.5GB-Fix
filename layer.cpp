#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>
#include <string.h>

// Your Hook Function
VKAPI_ATTR void VKAPI_CALL Hook_GetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties) 
{
    // Call the real driver first (simplified logic for now)
    // Then apply your cap
    const VkDeviceSize LIMIT_35GB = 3758096384ULL; 
    
    for (uint32_t i = 0; i < pMemoryProperties->memoryHeapCount; i++) {
        if ((pMemoryProperties->memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) &&
            (pMemoryProperties->memoryHeaps[i].size > LIMIT_35GB)) {
            pMemoryProperties->memoryHeaps[i].size = LIMIT_35GB;
        }
    }
}

// THE HANDSHAKE: This tells Vulkan your DLL is a real layer
extern "C" {
    VK_LAYER_EXPORT VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct) {
        if (pVersionStruct->loaderLayerInterfaceVersion < 2) return VK_ERROR_INITIALIZATION_FAILED;
        pVersionStruct->loaderLayerInterfaceVersion = 2;
        return VK_SUCCESS;
    }

    VK_LAYER_EXPORT PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName) {
        if (strcmp(pName, "vkGetPhysicalDeviceMemoryProperties") == 0) return (PFN_vkVoidFunction)Hook_GetPhysicalDeviceMemoryProperties;
        return nullptr;
    }

    VK_LAYER_EXPORT PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName) {
        return nullptr;
    }
}
