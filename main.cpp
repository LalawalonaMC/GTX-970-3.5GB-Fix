#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
    VkInstance instance;
    VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    vkCreateInstance(&createInfo, nullptr, &instance);

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(device, &props);
        
        VkPhysicalDeviceMemoryProperties memProps;
        vkGetPhysicalDeviceMemoryProperties(device, &memProps);

        std::cout << "Device: " << props.deviceName << "\n";
        for (uint32_t i = 0; i < memProps.memoryHeapCount; i++) {
            if (memProps.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                float gb = memProps.memoryHeaps[i].size / (1024.0 * 1024.0 * 1024.0);
                std::cout << "-> VRAM Heap " << i << ": " << gb << " GB\n";
            }
        }
    }

    vkDestroyInstance(instance, nullptr);
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
