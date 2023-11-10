#include "LIBGPU.H"
#include "EMULATOR_RENDER_VULKAN.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include "Core/EMULATOR_VERSION.H"
#include <stdio.h>

#if defined(VULKAN)

const char* renderBackendName = "Vulkan";

extern void Emulator_CreateVertexBuffer();
extern void Emulator_CreateIndexBuffer();
extern void Emulator_CreateGraphicsPipelineState(ShaderID* shader);
extern VkCommandBuffer Emulator_BeginSingleTimeCommands();
extern void Emulator_CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
extern int Emulator_BeginCommandBuffer();
extern void Emulator_UpdateVRAM();
extern void Emulator_TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
extern void Emulator_WaitForTimestep(int count);
extern void Emulator_UpdateProjectionConstantBuffer(float* ortho);
extern unsigned int Emulator_FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
extern void Emulator_EndSingleTimeCommands(VkCommandBuffer commandBuffer);
extern void Emulator_DestroyVulkanRenderPass();
extern void Emulator_DestroyVulkanFrameBuffers();
extern void Emulator_CreateVulkanRenderPass();
extern void Emulator_DestroyGlobalShaders();
extern void Emulator_CreateVulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
extern void Emulator_DestroyConstantBuffers();
extern void Emulator_CreateGlobalShaders();
extern void Emulator_CreatePipelineState(ShaderID* shader, VkPipeline* pipeline, VkPipelineColorBlendStateCreateInfo* colourBlendState);
extern VkImageView Emulator_CreateImageView(VkImage image, VkFormat format);
extern void Emulator_CreateRasterState(int wireframe);
extern void Emulator_CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
extern void Emulator_CreateConstantBuffers();
extern void Emulator_SetViewPort(int x, int y, int width, int height);
extern void Emulator_SetShader(const ShaderID shader);

#include "shaders/Vulkan/gte_shader_4_vs.h"
#include "shaders/Vulkan/gte_shader_4_ps.h"
#include "shaders/Vulkan/gte_shader_8_vs.h"
#include "shaders/Vulkan/gte_shader_8_ps.h"
#include "shaders/Vulkan/gte_shader_16_vs.h"
#include "shaders/Vulkan/gte_shader_16_ps.h"
#include "shaders/Vulkan/blit_shader_vs.h"
#include "shaders/Vulkan/blit_shader_ps.h"

VkBuffer dynamic_vertex_buffer;
VkDeviceMemory dynamic_vertex_buffer_memory;

VkBuffer dynamic_index_buffer;
VkDeviceMemory dynamic_index_buffer_memory;

int g_CurrentBlendMode = BM_NONE;

std::vector<const char*> g_validationLayers = {
		"VK_LAYER_KHRONOS_validation"
};

std::vector<const char*> g_availableExtensions = {
	"VK_EXT_debug_report"
};
VkInstance g_vkInstance;

VkDebugReportCallbackEXT g_debugCallback;

VkSurfaceKHR g_surface;

VkPhysicalDevice physical_devices;

unsigned int graphics_QueueFamilyIndex;
unsigned int present_QueueFamilyIndex;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

VkDevice device;
VkQueue graphicsQueue;
VkQueue presentQueue;

VkSwapchainKHR swapchain;

VkSurfaceCapabilitiesKHR surfaceCapabilities;
VkSurfaceFormatKHR surfaceFormat;
VkExtent2D swapchainSize;

std::vector<VkImage> swapchainImages;
uint32_t swapchainImageCount;
std::vector<VkImageView> swapchainImageViews;

VkRenderPass render_pass;
std::vector<VkFramebuffer> swapchainFramebuffers;

VkCommandPool commandPool;
std::vector<VkCommandBuffer> commandBuffers;

std::vector<VkSemaphore> imageAvailableSemaphores;
std::vector<VkSemaphore> renderFinishedSemaphores;
std::vector<VkFence> inFlightFences;

#define VERTEX_BIT (0)
#define FRAGMENT_BIT (1)

ShaderID g_activeShader;
TextureID g_activeTexture;

VkPipelineShaderStageCreateInfo g_shaderStages[2];
std::array<VkVertexInputAttributeDescription, 3> g_attributeDescriptions;
std::array<VkVertexInputAttributeDescription, 3> g_attributeDescriptionsBlit;
VkVertexInputBindingDescription g_bindingDescription;
VkVertexInputBindingDescription g_bindingDescriptionBlit;

VkViewport g_viewport;
VkPipelineRasterizationStateCreateInfo g_rasterizer;
VkClearValue clearValue;
unsigned int frameIndex;
unsigned int currentFrame = 0;
const int MAX_FRAMES_IN_FLIGHT = 2;

std::vector<VkBuffer> uniformBuffers;
std::vector<VkDeviceMemory> uniformBuffersMemory;
VkDescriptorPool descriptorPool[2];
VkDescriptorSetLayout descriptorSetLayout[2];
std::vector<VkDescriptorSet> descriptorSets[2];
int g_activeDescriptor = 0;

unsigned int g_vertexBufferMemoryBound = FALSE;
unsigned int imageIndex = 0;
bool begin_pass_flag = FALSE;
bool begin_commands_flag = FALSE;

SDL_Window* g_window = NULL;

int g_overrideWidth = -1;
int g_overrideHeight = -1;

ShaderID* g_shaders[] = { &g_gte_shader_4, &g_gte_shader_8, &g_gte_shader_16, &g_blit_shader };

#define Shader_Compile(name) Shader_Compile_Internal((unsigned int*)name##_vs, (unsigned int*)name##_ps, sizeof(name##_vs), sizeof(name##_ps))

ShaderID Shader_Compile_Internal(const unsigned int* vs_data, const unsigned int* ps_data, const unsigned int vs_size, const unsigned int ps_size)
{
	ShaderID shader;

	static int shaderType = 0;

	VkShaderModuleCreateInfo createInfo;
	memset(&createInfo, 0, sizeof(VkShaderModuleCreateInfo));

	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = vs_size;
	createInfo.pCode = (const uint32_t*)vs_data;

	shader.VS.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shader.VS.stage = VK_SHADER_STAGE_VERTEX_BIT;
	shader.VS.pName = "main";
	shader.VS.flags = 0;
	shader.VS.pNext = NULL;
	shader.VS.pSpecializationInfo = NULL;

	if (vkCreateShaderModule(device, &createInfo, NULL, &shader.VS.module) != VK_SUCCESS)
	{
		assert(FALSE);
	}

	memset(&createInfo, 0, sizeof(VkShaderModuleCreateInfo));
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = ps_size;
	createInfo.pCode = (const uint32_t*)ps_data;

	shader.PS.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shader.PS.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shader.PS.pName = "main";
	shader.PS.flags = 0;
	shader.PS.pNext = NULL;
	shader.PS.pSpecializationInfo = NULL;

	if (vkCreateShaderModule(device, &createInfo, NULL, &shader.PS.module) != VK_SUCCESS)
	{
		assert(FALSE);
	}

#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	memset(&g_attributeDescriptions[0], 0, sizeof(VkVertexInputAttributeDescription));
	memset(&g_attributeDescriptions[1], 0, sizeof(VkVertexInputAttributeDescription));
	memset(&g_attributeDescriptions[2], 0, sizeof(VkVertexInputAttributeDescription));

#if defined(PGXP)
	g_attributeDescriptions[0].binding = 0;
	g_attributeDescriptions[0].location = 0;
	g_attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	g_attributeDescriptions[0].offset = OFFSETOF(Vertex, x);
#else
	g_attributeDescriptions[0].binding = 0;
	g_attributeDescriptions[0].location = 0;
	g_attributeDescriptions[0].format = VK_FORMAT_R16G16B16A16_SINT;
	g_attributeDescriptions[0].offset = OFFSETOF(Vertex, x);
#endif

	g_attributeDescriptions[1].binding = 0;
	g_attributeDescriptions[1].location = 1;
	g_attributeDescriptions[1].format = VK_FORMAT_R8G8B8A8_UINT;
	g_attributeDescriptions[1].offset = OFFSETOF(Vertex, u);

	g_attributeDescriptions[2].binding = 0;
	g_attributeDescriptions[2].location = 2;
	g_attributeDescriptions[2].format = VK_FORMAT_R8G8B8A8_UNORM;
	g_attributeDescriptions[2].offset = OFFSETOF(Vertex, r);


	memset(&g_bindingDescription, 0, sizeof(VkVertexInputBindingDescription));
	g_bindingDescription.binding = 0;
	g_bindingDescription.stride = sizeof(Vertex);
	g_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;


	///@FIXME can be created more than once on same pointer? bug!
	VkPhysicalDeviceProperties properties;
	memset(&properties, 0, sizeof(VkPhysicalDeviceProperties));

	vkGetPhysicalDeviceProperties(physical_devices, &properties);

	VkSamplerCreateInfo samplerInfo;
	memset(&samplerInfo, 0, sizeof(VkSamplerCreateInfo));

	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_NEAREST;
	samplerInfo.minFilter = VK_FILTER_NEAREST;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_FALSE;
	samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(device, &samplerInfo, nullptr, &shader.SS) != VK_SUCCESS)
	{
		eprinterr("Failed to create sampler state!\n");
	}

	VkSamplerCreateInfo samplerInfoLUT;
	memset(&samplerInfoLUT, 0, sizeof(VkSamplerCreateInfo));

	samplerInfoLUT.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfoLUT.magFilter = VK_FILTER_NEAREST;
	samplerInfoLUT.minFilter = VK_FILTER_NEAREST;
	samplerInfoLUT.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfoLUT.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfoLUT.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfoLUT.anisotropyEnable = VK_FALSE;
	samplerInfoLUT.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	samplerInfoLUT.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfoLUT.unnormalizedCoordinates = VK_FALSE;
	samplerInfoLUT.compareEnable = VK_FALSE;
	samplerInfoLUT.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfoLUT.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(device, &samplerInfoLUT, nullptr, &shader.SSLUT) != VK_SUCCESS)
	{
		eprinterr("Failed to create sampler state!\n");
	}

	VkDescriptorSetLayoutBinding descriptorLayoutUniformBuffer = { 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT, NULL };
	VkDescriptorSetLayoutBinding descriptorLayoutTexture = { 2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, NULL };
	VkDescriptorSetLayoutBinding descriptorLayoutTexture2 = { 3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, NULL };

	VkDescriptorSetLayoutBinding bindings[] =
	{
		descriptorLayoutUniformBuffer,
		descriptorLayoutTexture,
		descriptorLayoutTexture2,
	};

	VkDescriptorSetLayoutCreateInfo resourceLayoutInfo;
	memset(&resourceLayoutInfo, 0, sizeof(VkDescriptorSetLayoutCreateInfo));
	resourceLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	resourceLayoutInfo.pNext = NULL;
	resourceLayoutInfo.bindingCount = 3;
	resourceLayoutInfo.pBindings = bindings;

	vkCreateDescriptorSetLayout(device, &resourceLayoutInfo, NULL, &shader.DL);


	VkPipelineLayoutCreateInfo pipelineLayoutInfo;
	memset(&pipelineLayoutInfo, 0, sizeof(VkPipelineLayoutCreateInfo));
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &shader.DL;

	if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, NULL, &shader.PL) != VK_SUCCESS)
	{
		eprinterr("Failed to create pipeline layout!\n");
		assert(FALSE);
	}

	Emulator_CreateGraphicsPipelineState(&shader);

	shader.T = (enum ShaderID::ShaderType)shaderType++;

#undef OFFSETOF

	return shader;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanReportFunc(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
{
	printf("VULKAN VALIDATION: %s\n", msg);
	return VK_FALSE;
}

PFN_vkGetInstanceProcAddr SDL2_vkGetInstanceProcAddr = VK_NULL_HANDLE;
PFN_vkCreateDebugReportCallbackEXT SDL2_vkCreateDebugReportCallbackEXT = VK_NULL_HANDLE;

void Emulator_CreateVulkanDebugLayer()
{
	SDL2_vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_Vulkan_GetVkGetInstanceProcAddr();
	SDL2_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_vkInstance, "vkCreateDebugReportCallbackEXT");

	VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo;
	memset(&debugCallbackCreateInfo, 0, sizeof(VkDebugReportCallbackCreateInfoEXT));
	debugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	debugCallbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	debugCallbackCreateInfo.pfnCallback = VulkanReportFunc;

	SDL2_vkCreateDebugReportCallbackEXT(g_vkInstance, &debugCallbackCreateInfo, NULL, &g_debugCallback);
}

int Emulator_CreateVulkanSurface()
{
	return SDL_Vulkan_CreateSurface(g_window, g_vkInstance, &g_surface);
}

int Emulator_CreateVulkanInstance(char* windowName)
{
	unsigned int numExtensions = 0;
	SDL_Vulkan_GetInstanceExtensions(g_window, &numExtensions, NULL);

	unsigned int additionalExtensionsCount = g_availableExtensions.size();
	numExtensions += additionalExtensionsCount;
	g_availableExtensions.resize(numExtensions);

	SDL_Vulkan_GetInstanceExtensions(g_window, &numExtensions, g_availableExtensions.data() + additionalExtensionsCount);

	VkApplicationInfo appInfo;
	memset(&appInfo, 0, sizeof(VkApplicationInfo));

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = windowName;
	appInfo.apiVersion = VK_API_VERSION_1_3;
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = EMULATOR_NAME;


	VkInstanceCreateInfo createInfo;
	memset(&createInfo, 0, sizeof(VkInstanceCreateInfo));

	//unsigned int layerCount;
	//vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	//g_validationLayers.resize(layerCount);
	//vkEnumerateInstanceLayerProperties(&layerCount, g_validationLayers.data());

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = g_validationLayers.size();
	createInfo.ppEnabledLayerNames = g_validationLayers.data();
	createInfo.enabledExtensionCount = g_availableExtensions.size();
	createInfo.ppEnabledExtensionNames = g_availableExtensions.data();

	return vkCreateInstance(&createInfo, NULL, &g_vkInstance);
}

void Emulator_SelectVulkanPhysicalDevice()
{
	std::vector<VkPhysicalDevice> physicalDevices;
	unsigned int physicalDeviceCount = 0;

	vkEnumeratePhysicalDevices(g_vkInstance, &physicalDeviceCount, NULL);
	physicalDevices.resize(physicalDeviceCount);
	vkEnumeratePhysicalDevices(g_vkInstance, &physicalDeviceCount, physicalDevices.data());

	physical_devices = physicalDevices[0];
}

void Emulator_SelectVulkanQueueFamily()
{
	std::vector<VkQueueFamilyProperties> queueFamilyProperties;
	unsigned int queueFamilyCount;

	vkGetPhysicalDeviceQueueFamilyProperties(physical_devices, &queueFamilyCount, NULL);
	queueFamilyProperties.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physical_devices, &queueFamilyCount, queueFamilyProperties.data());

	int graphicIndex = -1;
	int presentIndex = -1;

	int i = 0;
	for (const auto& queueFamily : queueFamilyProperties)
	{
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			graphicIndex = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physical_devices, i, g_surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport)
		{
			presentIndex = i;
		}

		if (graphicIndex != -1 && presentIndex != -1)
		{
			break;
		}

		i++;
	}

	graphics_QueueFamilyIndex = graphicIndex;
	present_QueueFamilyIndex = presentIndex;
}

int Emulator_CreateVulkanDevice()
{
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	const float queue_priority[] = { 1.0f };

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { graphics_QueueFamilyIndex, present_QueueFamilyIndex };

	float queuePriority = queue_priority[0];
	for (int queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = graphics_QueueFamilyIndex;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = queueCreateInfos.size();
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = deviceExtensions.size();
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	createInfo.enabledLayerCount = validationLayers.size();
	createInfo.ppEnabledLayerNames = validationLayers.data();

	VkResult result = vkCreateDevice(physical_devices, &createInfo, NULL, &device);

	vkGetDeviceQueue(device, graphics_QueueFamilyIndex, 0, &graphicsQueue);
	vkGetDeviceQueue(device, present_QueueFamilyIndex, 0, &presentQueue);

	return result;
}

int Emulator_CreateVulkanSwapChain()
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_devices, g_surface, &surfaceCapabilities);

	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	uint32_t surfaceFormatsCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physical_devices, g_surface, &surfaceFormatsCount, NULL);
	surfaceFormats.resize(surfaceFormatsCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physical_devices, g_surface, &surfaceFormatsCount, surfaceFormats.data());

	if (surfaceFormats[0].format != VK_FORMAT_B8G8R8A8_UNORM)
	{
		return FALSE;
	}

	surfaceFormat = surfaceFormats[0];
	swapchainSize.width = windowWidth;
	swapchainSize.height = windowHeight;

	unsigned int imageCount = surfaceCapabilities.minImageCount + 1;
	if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount)
	{
		imageCount = surfaceCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = g_surface;
	createInfo.minImageCount = surfaceCapabilities.minImageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = swapchainSize;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	unsigned int queueFamilyIndices[] = { graphics_QueueFamilyIndex, present_QueueFamilyIndex };
	if (graphics_QueueFamilyIndex != present_QueueFamilyIndex)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = surfaceCapabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	createInfo.clipped = VK_TRUE;

	vkCreateSwapchainKHR(device, &createInfo, NULL, &swapchain);

	vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, NULL);
	swapchainImages.resize(swapchainImageCount);
	vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages.data());

	return TRUE;
}

VkImageView Emulator_CreateVulkanImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
{
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		eprinterr("Failed to create image view!\n");
	}

	return imageView;
}


void Emulator_CreateVulkanImageViews()
{
	swapchainImageViews.resize(swapchainImages.size());

	for (unsigned int i = 0; i < swapchainImages.size(); i++)
	{
		swapchainImageViews[i] = Emulator_CreateVulkanImageView(swapchainImages[i], surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void Emulator_DestroyVulkanImageViews()
{
	for (unsigned int i = 0; i < swapchainImages.size(); i++)
	{
		vkDestroyImageView(device, swapchainImageViews[i], NULL);
	}

	swapchainImageViews.clear();
}

unsigned int Emulator_FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physical_devices, &memProperties);

	for (unsigned int i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	eprinterr("Failed to find memory type!\n");
	return 0;//?
}

VkBool32 Emulator_GetSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat)
{
	std::vector<VkFormat> depthFormats = {
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM
	};

	for (auto& format : depthFormats)
	{
		VkFormatProperties formatProps;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
		if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			*depthFormat = format;
			return true;
		}
	}

	return false;
}

void Emulator_DestroySyncObjects()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroySemaphore(device, renderFinishedSemaphores[i], NULL);
		vkDestroySemaphore(device, imageAvailableSemaphores[i], NULL);
		vkDestroyFence(device, inFlightFences[i], NULL);

		renderFinishedSemaphores[i] = VK_NULL_HANDLE;
		imageAvailableSemaphores[i] = VK_NULL_HANDLE;
		inFlightFences[i] = VK_NULL_HANDLE;
	}

	renderFinishedSemaphores.clear();
	imageAvailableSemaphores.clear();
	inFlightFences.clear();
}

void Emulator_DestroyDescriptorSetLayout()
{
	for (int i = 0; i < 2; i++)
	{
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout[i], NULL);
	}
}

void Emulator_DestroyDescriptorPool()
{
	for (int i = 0; i < 2; i++)
	{
		vkDestroyDescriptorPool(device, descriptorPool[i], NULL);
		descriptorPool[i] = VK_NULL_HANDLE;
	}
}

void Emulator_DestroyVulkanCommandBuffers()
{
	for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkFreeCommandBuffers(device, commandPool, 1, &commandBuffers[i]);
	}

	commandBuffers.clear();
}

void Emulator_DestroyVulkanCommandPool()
{
	vkDestroyCommandPool(device, commandPool, NULL);
	commandPool = VK_NULL_HANDLE;
}

void Emulator_CreateVulkanFrameBuffers()
{
	swapchainFramebuffers.resize(swapchainImageViews.size());

	for (unsigned int i = 0; i < swapchainImageViews.size(); i++)
	{
		std::vector<VkImageView> attachments(1);
		attachments[0] = swapchainImageViews[i];
		//attachments[1] = depthImageView;

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = render_pass;
		framebufferInfo.attachmentCount = static_cast<unsigned int>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = swapchainSize.width;
		framebufferInfo.height = swapchainSize.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, NULL, &swapchainFramebuffers[i]) != VK_SUCCESS)
		{
			eprinterr("Failed to create vulkan frame buffer!\n");
		}
	}
}

void Emulator_CreateVulkanCommandPool()
{
	VkCommandPoolCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	createInfo.queueFamilyIndex = graphics_QueueFamilyIndex;
	vkCreateCommandPool(device, &createInfo, nullptr, &commandPool);
}

void Emulator_CreateVulkanCommandBuffers()
{
	commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate command buffers!\n");
		assert(FALSE);
	}
}

void Emulator_CreateDescriptorPool()
{
	for (int i = 0; i < 2; i++)
	{
		std::array<VkDescriptorPoolSize, 3> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[2].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

		if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool[i]) != VK_SUCCESS)
		{
			eprinterr("Failed to create descriptor pool!\n");
		}
	}
}

void Emulator_CreateSyncObjects()
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
		{
			eprinterr("Failed to create sync objects!\n");
			assert(FALSE);
		}
	}
}

void Emulator_CreateUniformBuffers()
{
	VkDeviceSize bufferSize = sizeof(float) * 16;

	uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		Emulator_CreateVulkanBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
	}
}

void Emulator_CreateDescriptorSetLayout()
{
	for (int i = 0; i < 2; i++)
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = NULL;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding textureLayoutBinding{};
		textureLayoutBinding.binding = 2;
		textureLayoutBinding.descriptorCount = 1;
		textureLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		textureLayoutBinding.pImmutableSamplers = NULL;
		textureLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		VkDescriptorSetLayoutBinding textureLayoutBinding2{};
		textureLayoutBinding2.binding = 3;
		textureLayoutBinding2.descriptorCount = 1;
		textureLayoutBinding2.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		textureLayoutBinding2.pImmutableSamplers = NULL;
		textureLayoutBinding2.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		std::array<VkDescriptorSetLayoutBinding, 3> bindings = { uboLayoutBinding, textureLayoutBinding, textureLayoutBinding2 };
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout[i]) != VK_SUCCESS)
		{
			eprinterr("Failed to create descriptor set layout!");
			assert(FALSE);
		}
	}
}

void Emulator_ResetDevice(int recreate)
{
	if (dynamic_vertex_buffer) {
		vkDestroyBuffer(device, dynamic_vertex_buffer, NULL);
		dynamic_vertex_buffer = VK_NULL_HANDLE;
	}

	if (dynamic_index_buffer) {
		vkDestroyBuffer(device, dynamic_index_buffer, NULL);
		dynamic_index_buffer = VK_NULL_HANDLE;
	}

	enum ShaderID::ShaderType lastShaderBound = g_activeShader.T;

	Emulator_DestroySyncObjects();
	Emulator_DestroyGlobalShaders();
	Emulator_DestroyConstantBuffers();
	Emulator_DestroyDescriptorSetLayout();
	Emulator_DestroyDescriptorPool();
	Emulator_DestroyVulkanCommandBuffers();
	Emulator_DestroyVulkanCommandPool();
	Emulator_DestroyVulkanFrameBuffers();
	Emulator_DestroyVulkanRenderPass();
	Emulator_DestroyVulkanImageViews();

	vkDestroySwapchainKHR(device, swapchain, NULL);
	swapchain = VK_NULL_HANDLE;
	swapchainImages.clear();

	vkDestroyImageView(device, vramTexture.textureImageView, NULL);
	vkDestroyImage(device, vramTexture.textureImage, NULL);
	vkFreeMemory(device, vramTexture.textureImageMemory, NULL);
	vkDestroyBuffer(device, vramTexture.stagingBuffer, NULL);
	vkFreeMemory(device, vramTexture.stagingBufferMemory, NULL);

	vkDestroyImageView(device, whiteTexture.textureImageView, NULL);
	vkDestroyImage(device, whiteTexture.textureImage, NULL);
	vkFreeMemory(device, whiteTexture.textureImageMemory, NULL);
	vkDestroyBuffer(device, whiteTexture.stagingBuffer, NULL);
	vkFreeMemory(device, whiteTexture.stagingBufferMemory, NULL);

	vkDestroyImageView(device, rg8lutTexture.textureImageView, NULL);
	vkDestroyImage(device, rg8lutTexture.textureImage, NULL);
	vkFreeMemory(device, rg8lutTexture.textureImageMemory, NULL);
	vkDestroyBuffer(device, rg8lutTexture.stagingBuffer, NULL);
	vkFreeMemory(device, rg8lutTexture.stagingBufferMemory, NULL);

	vkDestroyDevice(device, NULL);
	device = VK_NULL_HANDLE;

	Emulator_SelectVulkanPhysicalDevice();
	Emulator_SelectVulkanQueueFamily();

	if (Emulator_CreateVulkanDevice() != VK_SUCCESS)
	{
		eprinterr("Failed to create device (vkCreateDevice)!\n");
		assert(FALSE);
		return;
	}

	if (Emulator_CreateVulkanSwapChain() != TRUE)
	{
		eprinterr("Failed to create vulkan swap chain!\n");
		assert(FALSE);
		return;
	}

	Emulator_CreateVulkanImageViews();
	Emulator_CreateVulkanRenderPass();
	Emulator_CreateVulkanFrameBuffers();
	Emulator_CreateVulkanCommandPool();
	Emulator_CreateVulkanCommandBuffers();
	Emulator_CreateSyncObjects();
	Emulator_CreateUniformBuffers();
	Emulator_CreateDescriptorPool();//TOFREE
	Emulator_CreateDescriptorSetLayout();//TOFREE

	unsigned int pixelData = 0xFFFFFFFF;
	int texWidth = 1;
	int texHeight = 1;
	VkDeviceSize imageSize = texWidth * texHeight * sizeof(unsigned int);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, whiteTexture.stagingBuffer, whiteTexture.stagingBufferMemory);

	void* data = NULL;
	vkMapMemory(device, whiteTexture.stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, &pixelData, static_cast<size_t>(imageSize));
	vkUnmapMemory(device, whiteTexture.stagingBufferMemory);

	Emulator_CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, whiteTexture.textureImage, whiteTexture.textureImageMemory);
	whiteTexture.textureImageView = Emulator_CreateImageView(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM);

	Emulator_TransitionImageLayout(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_CopyBufferToImage(whiteTexture.stagingBuffer, whiteTexture.textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
	Emulator_TransitionImageLayout(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	texWidth = VRAM_WIDTH;
	texHeight = VRAM_HEIGHT;
	imageSize = texWidth * texHeight * sizeof(unsigned short);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vramTexture.stagingBuffer, vramTexture.stagingBufferMemory);
	Emulator_CreateImage(texWidth, texHeight, VK_FORMAT_R8G8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vramTexture.textureImage, vramTexture.textureImageMemory);
	vramTexture.textureImageView = Emulator_CreateImageView(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM);

	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	imageSize = LUT_WIDTH * LUT_HEIGHT * sizeof(unsigned int);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, rg8lutTexture.stagingBuffer, rg8lutTexture.stagingBufferMemory);

	data = NULL;
	vkMapMemory(device, rg8lutTexture.stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, Emulator_GenerateRG8LUT(), static_cast<size_t>(imageSize));
	vkUnmapMemory(device, rg8lutTexture.stagingBufferMemory);

	Emulator_CreateImage(LUT_WIDTH, LUT_HEIGHT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, rg8lutTexture.textureImage, rg8lutTexture.textureImageMemory);
	rg8lutTexture.textureImageView = Emulator_CreateImageView(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM);

	Emulator_TransitionImageLayout(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_CopyBufferToImage(rg8lutTexture.stagingBuffer, rg8lutTexture.textureImage, static_cast<uint32_t>(LUT_WIDTH), static_cast<uint32_t>(LUT_HEIGHT));
	Emulator_TransitionImageLayout(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);


	Emulator_CreateGlobalShaders();

	Emulator_CreateVertexBuffer();

	Emulator_CreateIndexBuffer();

	currentFrame = 0;

	g_vertexBufferMemoryBound = FALSE;

	if (begin_pass_flag)
	{
		begin_commands_flag = FALSE;
		begin_pass_flag = FALSE;
		Emulator_BeginPass();
	}
	else if (begin_commands_flag)
	{
		begin_commands_flag = FALSE;
		Emulator_BeginCommandBuffer();
	}
}

int Emulator_InitialiseVulkanContext(char* windowName)
{
#if defined(SDL2)
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}
#endif

	if (Emulator_CreateVulkanInstance(windowName))
	{
		eprinterr("Failed to create instance (vkCreateInstance)!\n");
		return FALSE;
	}

#if defined(_DEBUG)
	Emulator_CreateVulkanDebugLayer();
#endif

	if (Emulator_CreateVulkanSurface() == SDL_FALSE)
	{
		eprinterr("Failed to create vulkan surface!\n");
		return FALSE;
	}

	Emulator_SelectVulkanPhysicalDevice();
	Emulator_SelectVulkanQueueFamily();

	if (Emulator_CreateVulkanDevice() != VK_SUCCESS)
	{
		eprinterr("Failed to create device (vkCreateDevice)!\n");
		return FALSE;
	}

	if (Emulator_CreateVulkanSwapChain() != TRUE)
	{
		eprinterr("Failed to create vulkan swap chain!\n");
		return FALSE;
	}

	Emulator_CreateVulkanImageViews();
	Emulator_CreateVulkanRenderPass();
	Emulator_CreateVulkanFrameBuffers();
	Emulator_CreateVulkanCommandPool();
	Emulator_CreateVulkanCommandBuffers();
	Emulator_CreateSyncObjects();
	Emulator_CreateUniformBuffers();
	Emulator_CreateDescriptorPool();
	Emulator_CreateDescriptorSetLayout();

	return TRUE;
}


void Emulator_UpdateDescriptorSets()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			TextureID texture;

			if (j == 0)
			{
				texture = vramTexture;
			}
			else
			{
				texture = whiteTexture;
			}

			VkDescriptorBufferInfo uniformInfo{};
			uniformInfo.buffer = uniformBuffers[i];
			uniformInfo.offset = 0;
			uniformInfo.range = sizeof(float) * 16;

			VkDescriptorImageInfo samplerInfo{};
			samplerInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			samplerInfo.imageView = texture.textureImageView;
			samplerInfo.sampler = g_shaders[0]->SS;

			VkDescriptorImageInfo textureInfo{};
			textureInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			textureInfo.imageView = rg8lutTexture.textureImageView;
			textureInfo.sampler = g_shaders[0]->SSLUT;

			std::array<VkWriteDescriptorSet, 3> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = descriptorSets[i][j];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pBufferInfo = &uniformInfo;

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = descriptorSets[i][j];
			descriptorWrites[1].dstBinding = 2;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[1].descriptorCount = 1;
			descriptorWrites[1].pImageInfo = &samplerInfo;

			descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[2].dstSet = descriptorSets[i][j];
			descriptorWrites[2].dstBinding = 3;
			descriptorWrites[2].dstArrayElement = 0;
			descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[2].descriptorCount = 1;
			descriptorWrites[2].pImageInfo = &textureInfo;

			vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, NULL);
		}
	}
}

void Emulator_CreateDescriptorSets()
{
	for (int i = 0; i < 2; i++)
	{
		std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout[i]);
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = descriptorPool[i];
		allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		allocInfo.pSetLayouts = layouts.data();

		descriptorSets[i].resize(MAX_FRAMES_IN_FLIGHT);
		if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets[i].data()) != VK_SUCCESS)
		{
			eprinterr("Failed to allocate descriptor sets!\n");
		}
	}

	Emulator_UpdateDescriptorSets();
}

void Emulator_CreateGlobalShaders()
{
	Emulator_CreateRasterState(FALSE);

	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);

	g_gte_shader_4 = Shader_Compile(gte_shader_4);
	g_gte_shader_8 = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader = Shader_Compile(blit_shader);

	Emulator_CreateDescriptorSets();

	Emulator_SetShader(g_gte_shader_4);
}

void Emulator_DestroyGlobalShaders()
{
	if (g_gte_shader_4.VS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_4.VS.module, NULL);
		g_gte_shader_4.VS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_4.PS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_4.PS.module, NULL);
		g_gte_shader_4.PS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_4.DL)
	{
		vkDestroyDescriptorSetLayout(device, g_gte_shader_4.DL, NULL);
		g_gte_shader_4.DL = VK_NULL_HANDLE;
	}

	if (g_gte_shader_4.PL)
	{
		vkDestroyPipelineLayout(device, g_gte_shader_4.PL, NULL);
		g_gte_shader_4.PL = VK_NULL_HANDLE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (g_gte_shader_4.GP)
		{
			vkDestroyPipeline(device, g_gte_shader_4.GP[i], NULL);
			g_gte_shader_4.GP[i] = VK_NULL_HANDLE;
		}
	}

	if (g_gte_shader_4.SS)
	{
		vkDestroySampler(device, g_gte_shader_4.SS, NULL);
		g_gte_shader_4.SS = VK_NULL_HANDLE;
	}

	if (g_gte_shader_8.VS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_8.VS.module, NULL);
		g_gte_shader_8.VS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_8.PS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_8.PS.module, NULL);
		g_gte_shader_8.PS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_8.DL)
	{
		vkDestroyDescriptorSetLayout(device, g_gte_shader_8.DL, NULL);
		g_gte_shader_8.DL = VK_NULL_HANDLE;
	}

	if (g_gte_shader_8.PL)
	{
		vkDestroyPipelineLayout(device, g_gte_shader_8.PL, NULL);
		g_gte_shader_8.PL = VK_NULL_HANDLE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (g_gte_shader_8.GP)
		{
			vkDestroyPipeline(device, g_gte_shader_8.GP[i], NULL);
			g_gte_shader_8.GP[i] = VK_NULL_HANDLE;
		}
	}

	if (g_gte_shader_8.SS)
	{
		vkDestroySampler(device, g_gte_shader_8.SS, NULL);
		g_gte_shader_8.SS = VK_NULL_HANDLE;
	}

	if (g_gte_shader_16.VS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_16.VS.module, NULL);
		g_gte_shader_16.VS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_16.PS.module)
	{
		vkDestroyShaderModule(device, g_gte_shader_16.PS.module, NULL);
		g_gte_shader_16.PS.module = VK_NULL_HANDLE;
	}

	if (g_gte_shader_16.DL)
	{
		vkDestroyDescriptorSetLayout(device, g_gte_shader_16.DL, NULL);
		g_gte_shader_16.DL = VK_NULL_HANDLE;
	}

	if (g_gte_shader_16.PL)
	{
		vkDestroyPipelineLayout(device, g_gte_shader_16.PL, NULL);
		g_gte_shader_16.PL = VK_NULL_HANDLE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (g_gte_shader_16.GP)
		{
			vkDestroyPipeline(device, g_gte_shader_16.GP[i], NULL);
			g_gte_shader_16.GP[i] = VK_NULL_HANDLE;
		}
	}

	if (g_gte_shader_16.SS)
	{
		vkDestroySampler(device, g_gte_shader_16.SS, NULL);
		g_gte_shader_16.SS = VK_NULL_HANDLE;
	}

	if (g_blit_shader.VS.module)
	{
		vkDestroyShaderModule(device, g_blit_shader.VS.module, NULL);
		g_blit_shader.VS.module = VK_NULL_HANDLE;
	}

	if (g_blit_shader.PS.module)
	{
		vkDestroyShaderModule(device, g_blit_shader.PS.module, NULL);
		g_blit_shader.PS.module = VK_NULL_HANDLE;
	}

	if (g_blit_shader.DL)
	{
		vkDestroyDescriptorSetLayout(device, g_blit_shader.DL, NULL);
		g_blit_shader.DL = VK_NULL_HANDLE;
	}

	if (g_blit_shader.PL)
	{
		vkDestroyPipelineLayout(device, g_blit_shader.PL, NULL);
		g_blit_shader.PL = VK_NULL_HANDLE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (g_blit_shader.GP)
		{
			vkDestroyPipeline(device, g_blit_shader.GP[i], NULL);
			g_blit_shader.GP[i] = VK_NULL_HANDLE;
		}
	}

	if (g_blit_shader.SS)
	{
		vkDestroySampler(device, g_blit_shader.SS, NULL);
		g_blit_shader.SS = VK_NULL_HANDLE;
	}
}

void Emulator_GenerateCommonTextures()
{
	unsigned int pixelData = 0xFFFFFFFF;

	int texWidth = 1;
	int texHeight = 1;
	VkDeviceSize imageSize = texWidth * texHeight * sizeof(unsigned int);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, whiteTexture.stagingBuffer, whiteTexture.stagingBufferMemory);

	void* data = NULL;
	vkMapMemory(device, whiteTexture.stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, &pixelData, static_cast<size_t>(imageSize));
	vkUnmapMemory(device, whiteTexture.stagingBufferMemory);

	Emulator_CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, whiteTexture.textureImage, whiteTexture.textureImageMemory);
	whiteTexture.textureImageView = Emulator_CreateImageView(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM);

	Emulator_TransitionImageLayout(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_CopyBufferToImage(whiteTexture.stagingBuffer, whiteTexture.textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
	Emulator_TransitionImageLayout(whiteTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	imageSize = LUT_WIDTH * LUT_HEIGHT * sizeof(unsigned int);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, rg8lutTexture.stagingBuffer, rg8lutTexture.stagingBufferMemory);

	data = NULL;
	vkMapMemory(device, rg8lutTexture.stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, Emulator_GenerateRG8LUT(), static_cast<size_t>(imageSize));
	vkUnmapMemory(device, rg8lutTexture.stagingBufferMemory);

	Emulator_CreateImage(LUT_WIDTH, LUT_HEIGHT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, rg8lutTexture.textureImage, rg8lutTexture.textureImageMemory);
	rg8lutTexture.textureImageView = Emulator_CreateImageView(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM);

	Emulator_TransitionImageLayout(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_CopyBufferToImage(rg8lutTexture.stagingBuffer, rg8lutTexture.textureImage, static_cast<uint32_t>(LUT_WIDTH), static_cast<uint32_t>(LUT_HEIGHT));
	Emulator_TransitionImageLayout(rg8lutTexture.textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void Emulator_CreateVertexBuffer()
{
	Emulator_CreateVulkanBuffer(sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, dynamic_vertex_buffer, dynamic_vertex_buffer_memory);
}

void Emulator_CreateIndexBuffer()
{
	Emulator_CreateVulkanBuffer(sizeof(unsigned short) * MAX_NUM_INDEX_BUFFER_INDICES, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, dynamic_index_buffer, dynamic_index_buffer_memory);
}

int Emulator_CreateCommonResources()
{
	memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	
	Emulator_GenerateCommonTextures();

	Emulator_CreateConstantBuffers();
	
	///@FIXME move below to gen common textures
	int texWidth = VRAM_WIDTH;
	int texHeight = VRAM_HEIGHT;
	VkDeviceSize imageSize = texWidth * texHeight * sizeof(unsigned short);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vramTexture.stagingBuffer, vramTexture.stagingBufferMemory);
	Emulator_CreateImage(texWidth, texHeight, VK_FORMAT_R8G8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vramTexture.textureImage, vramTexture.textureImageMemory);
	vramTexture.textureImageView = Emulator_CreateImageView(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM);

	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	Emulator_CreateGlobalShaders();

	Emulator_ResetDevice(TRUE);

	return TRUE;
}

void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);

	float z = znear / (znear - zfar);

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

	Emulator_UpdateProjectionConstantBuffer(ortho);
}

void Emulator_SetShader(const ShaderID shader)
{
	g_shaderStages[VERTEX_BIT] = shader.VS;
	g_shaderStages[FRAGMENT_BIT] = shader.PS;
	g_activeShader = shader;

	if (begin_commands_flag && begin_pass_flag && !g_resetDeviceOnNextFrame)
	{
		vkCmdBindPipeline(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, shader.GP[g_CurrentBlendMode]);
	}

	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);
}

void Emulator_SetTextureAndShader(TextureID texture, ShaderID shader)
{
	Emulator_SetShader(shader);

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	///@FIXME broken!
	if (g_lastBoundTexture[0].textureImage == texture.textureImage && g_lastBoundTexture[1].textureImage == rg8lutTexture.textureImage) {
		//return;
	}

	g_activeTexture = texture;
	if (g_activeTexture.textureImage == vramTexture.textureImage)
	{
		g_activeDescriptor = 0;
	}
	else
	{
		g_activeDescriptor = 1;
	}

	vkCmdBindDescriptorSets(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, g_activeShader.PL, 0, 1, &descriptorSets[currentFrame][g_activeDescriptor], 0, NULL);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_SetTexture(TextureID texture, enum TexFormat texFormat)
{
	switch (texFormat)
	{
	case TF_4_BIT:
		Emulator_SetShader(g_gte_shader_4);
		break;
	case TF_8_BIT:
		Emulator_SetShader(g_gte_shader_8);
		break;
	case TF_16_BIT:
		Emulator_SetShader(g_gte_shader_16);
		break;
	}

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture[0].textureImage == texture.textureImage && g_lastBoundTexture[1].textureImage == rg8lutTexture.textureImage) {
		//return;
	}

	g_activeTexture = texture;
	if (g_activeTexture.textureImage == vramTexture.textureImage)
	{
		g_activeDescriptor = 0;
	}
	else
	{
		g_activeDescriptor = 1;
	}

	vkCmdBindDescriptorSets(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, g_activeShader.PL, 0, 1, &descriptorSets[currentFrame][g_activeDescriptor], 0, NULL);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_DestroyTexture(TextureID texture)
{
	UNIMPLEMENTED();
}

void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	///@FIXME had to implement a hack here, vkBeginRenderPass does clear to black after this.
	VkClearColorValue clearColor = { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };

	//VkClearValue clearValue;
	memset(&clearValue, 0, sizeof(VkClearValue));

	clearValue.color = clearColor;
	VkImageSubresourceRange imageRange;
	memset(&imageRange, 0, sizeof(VkImageSubresourceRange));

	imageRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	imageRange.levelCount = 1;
	imageRange.layerCount = 1;

	VkCommandBuffer buff = Emulator_BeginSingleTimeCommands();

	Emulator_TransitionImageLayout(swapchainImages[0], VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Emulator_EndSingleTimeCommands(buff);

	VkCommandBuffer buff2 = Emulator_BeginSingleTimeCommands();
	vkCmdClearColorImage(buff2, swapchainImages[0], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1, &imageRange);
	Emulator_EndSingleTimeCommands(buff2);

	VkCommandBuffer buff3 = Emulator_BeginSingleTimeCommands();
	Emulator_TransitionImageLayout(swapchainImages[0], VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
	Emulator_EndSingleTimeCommands(buff3);
}

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

	FILE* f = fopen(outputFileName, "wb");
	if (f == NULL)
	{
		return;
	}

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&vram[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&vram[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);

}

void Emulator_StoreFrameBuffer(int x, int y, int w, int h)
{
	short* fb = (short*)malloc(w * h * sizeof(short));

#define FLIP_Y (fy)
	int* data = NULL;
	assert(FALSE);//Needs implementing for framebuffer write backs!
	return;

	unsigned int* data_src = (unsigned int*)data;
	unsigned short* data_dst = (unsigned short*)fb;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			unsigned int  c = *data_src++;
			unsigned char b = ((c >> 3) & 0x1F);
			unsigned char g = ((c >> 11) & 0x1F);
			unsigned char r = ((c >> 19) & 0x1F);
#if defined(SWAP_RB)
			*data_dst++ = b | (g << 5) | (r << 10) | 0x8000;
#else
			* data_dst++ = r | (g << 5) | (b << 10) | 0x8000;
#endif
		}
	}

#if 0
	unsigned short* src = (unsigned short*)fb;
	unsigned short* dst = vram + x + y * VRAM_WIDTH;

	for (int i = 0; i < h; i++) {
		memcpy(dst, src, w * sizeof(unsigned short));
		src += w;
		dst += VRAM_WIDTH;
	}
#elif 1

	short* ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short* fb_ptr = fb + (h * FLIP_Y / h) * w;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[w * fx / w];
		}

		ptr += VRAM_WIDTH;
	}
#endif

#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_CreateRasterState(int wireframe)
{
	g_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	g_rasterizer.depthClampEnable = VK_FALSE;
	g_rasterizer.rasterizerDiscardEnable = VK_FALSE;
	g_rasterizer.polygonMode = wireframe ? VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_FILL;
	g_rasterizer.lineWidth = 1.0f;
	g_rasterizer.cullMode = VK_CULL_MODE_NONE;
	g_rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	g_rasterizer.depthBiasEnable = VK_FALSE;
}

void Emulator_CreatePipelineState(ShaderID* shader, VkPipeline* pipeline, VkPipelineColorBlendStateCreateInfo* colourBlendState)
{
	VkPipelineVertexInputStateCreateInfo vertexInputInfo;
	memset(&vertexInputInfo, 0, sizeof(VkPipelineVertexInputStateCreateInfo));

	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(g_attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &g_bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = g_attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly;
	memset(&inputAssembly, 0, sizeof(VkPipelineInputAssemblyStateCreateInfo));
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkRect2D scissor;
	scissor.extent.width = windowWidth;
	scissor.extent.height = windowHeight;
	scissor.offset.x = 0;
	scissor.offset.y = 0;

	VkPipelineViewportStateCreateInfo viewportState;
	memset(&viewportState, 0, sizeof(VkPipelineViewportStateCreateInfo));
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &g_viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineMultisampleStateCreateInfo multisampling;
	memset(&multisampling, 0, sizeof(VkPipelineMultisampleStateCreateInfo));

	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineShaderStageCreateInfo shaderStages[] = { shader->VS, shader->PS };

	VkGraphicsPipelineCreateInfo pipelineInfo;
	memset(&pipelineInfo, 0, sizeof(VkGraphicsPipelineCreateInfo));
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &g_rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = colourBlendState;

	pipelineInfo.layout = shader->PL;
	pipelineInfo.renderPass = render_pass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, pipeline) != VK_SUCCESS)
	{
		eprinterr("Failed to create graphics pipeline\n");
		assert(FALSE);
	}
}

VkCommandBuffer Emulator_BeginSingleTimeCommands()
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void Emulator_EndSingleTimeCommands(VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void Emulator_CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
	VkCommandBuffer commandBuffer = Emulator_BeginSingleTimeCommands();

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		width,
		height,
		1
	};

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	Emulator_EndSingleTimeCommands(commandBuffer);
}

void Emulator_TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkCommandBuffer commandBuffer = Emulator_BeginSingleTimeCommands();

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && (newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL || newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR))
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else
	{
		eprinterr("Unsupported layout transition!\n");
	}

	vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, NULL, 0, NULL, 1, &barrier);

	Emulator_EndSingleTimeCommands(commandBuffer);
}

void Emulator_CreateVulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(device, &bufferInfo, NULL, &buffer) != VK_SUCCESS)
	{
		eprinterr("Failed to create buffer!\n");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = Emulator_FindMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate buffer memory!\n");
	}

	vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void Emulator_EndCommandBuffer()
{
	if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS)
	{
		eprinterr("Failed to end command buffer!\n");
		assert(FALSE);
	}

	begin_commands_flag = FALSE;
}

void Emulator_EndPass()
{
	vkCmdEndRenderPass(commandBuffers[currentFrame]);

	Emulator_EndCommandBuffer();

	if (vram_need_update)
	{
		Emulator_UpdateVRAM();
	}

	begin_pass_flag = FALSE;
}

int Emulator_BeginCommandBuffer()
{
	if (begin_commands_flag)
	{
		return begin_commands_flag;
	}

	int last_begin_commands_flag = begin_commands_flag;

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo) != VK_SUCCESS)
	{
		eprinterr("Failed to begin recording command buffer!\n");
		assert(FALSE);
	}

	begin_commands_flag = TRUE;

	return last_begin_commands_flag;
}

void Emulator_BeginPass()
{
	if (vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX) != VK_SUCCESS)
	{
		eprinterr("Failed to wait for fences!\n");
		assert(FALSE);
	}

	VkResult result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		eprinterr("Failed to acquire next image!\n");
		assert(FALSE);
	}

	if (vkResetFences(device, 1, &inFlightFences[currentFrame]) != VK_SUCCESS)
	{
		eprinterr("Failed to reset fences!\n");
		assert(FALSE);
	}

	if (vkResetCommandBuffer(commandBuffers[currentFrame], 0) != VK_SUCCESS)
	{
		eprinterr("Failed to reset command buffer!\n");
		assert(FALSE);
	}

	Emulator_BeginCommandBuffer();

	VkExtent2D swapChainExtent;
	swapChainExtent.width = windowWidth;
	swapChainExtent.height = windowHeight;

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = render_pass;
	renderPassInfo.framebuffer = swapchainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChainExtent;

	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearValue;

	vkCmdBeginRenderPass(commandBuffers[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindDescriptorSets(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, g_activeShader.PL, 0, 1, &descriptorSets[currentFrame][g_activeDescriptor], 0, NULL);

	begin_pass_flag = TRUE;
}

VkImageView Emulator_CreateImageView(VkImage image, VkFormat format)
{
	VkImageViewCreateInfo viewInfo;
	memset(&viewInfo, 0, sizeof(VkImageViewCreateInfo));

	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		eprinterr("Failed to create image view!");
		assert(FALSE);
	}

	return imageView;
}

void Emulator_CreateConstantBuffers()
{
	VkDeviceSize bufferSize = sizeof(float) * 16;

	uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		Emulator_CreateVulkanBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
	}
}

void Emulator_UpdateProjectionConstantBuffer(float* ortho)
{
	void* data = NULL;
	vkMapMemory(device, uniformBuffersMemory[currentFrame], 0, sizeof(float) * 16, 0, &data);
	memcpy(data, ortho, sizeof(float) * 16);
	vkUnmapMemory(device, uniformBuffersMemory[currentFrame]);
}

void Emulator_DestroyConstantBuffers()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(device, uniformBuffers[i], NULL);
		vkFreeMemory(device, uniformBuffersMemory[i], NULL);
		uniformBuffers[i] = VK_NULL_HANDLE;
		uniformBuffersMemory[i] = VK_NULL_HANDLE;
	}
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

	TextureID newVramTexture;
	unsigned int texWidth = VRAM_WIDTH;
	unsigned int texHeight = VRAM_HEIGHT;
	unsigned int imageSize = texWidth * texHeight * sizeof(unsigned short);

	Emulator_CreateVulkanBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, newVramTexture.stagingBuffer, newVramTexture.stagingBufferMemory);

	void* data = NULL;
	vkMapMemory(device, newVramTexture.stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, vram, imageSize);
	vkUnmapMemory(device, newVramTexture.stagingBufferMemory);

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		texWidth,
		texHeight,
		1
	};

	VkCommandBuffer buff = Emulator_BeginSingleTimeCommands();

	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	vkCmdCopyBufferToImage(buff, newVramTexture.stagingBuffer, vramTexture.textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	Emulator_EndSingleTimeCommands(buff);

	Emulator_TransitionImageLayout(vramTexture.textureImage, VK_FORMAT_R8G8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(device, newVramTexture.stagingBuffer, NULL);
	vkFreeMemory(device, newVramTexture.stagingBufferMemory, NULL);
}

void Emulator_SetWireframe(int enable)
{
	Emulator_CreateRasterState(enable ? TRUE : FALSE);
}

void Emulator_SetBlendMode(enum BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

	g_CurrentBlendMode = blendMode;
	g_PreviousBlendMode = blendMode;
}

void Emulator_CreateGraphicsPipelineState(ShaderID* shader)
{
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlend;

	memset(&colorBlendAttachment, 0, sizeof(VkPipelineColorBlendAttachmentState));
	
	memset(&colorBlend, 0, sizeof(VkPipelineColorBlendStateCreateInfo));
	
	colorBlend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlend.logicOpEnable = VK_FALSE;
	colorBlend.logicOp = VK_LOGIC_OP_COPY;
	colorBlend.attachmentCount = 1;
	colorBlend.pAttachments = &colorBlendAttachment;

	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	for (int i = 0; i < BM_COUNT; i++)
	{
		switch (i)
		{
		case BM_NONE:
		{
			colorBlendAttachment.blendEnable = VK_FALSE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			colorBlend.blendConstants[0] = 1.0f;
			colorBlend.blendConstants[1] = 1.0f;
			colorBlend.blendConstants[2] = 1.0f;
			colorBlend.blendConstants[3] = 1.0f;
			break;
		}
		case BM_AVERAGE:
		{
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			colorBlend.blendConstants[0] = 128.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[1] = 128.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[2] = 128.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[3] = 128.0f * (1.0f / 255.0f);
			break;
		}
		case BM_ADD:
		{
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			colorBlend.blendConstants[0] = 1.0f;
			colorBlend.blendConstants[1] = 1.0f;
			colorBlend.blendConstants[2] = 1.0f;
			colorBlend.blendConstants[3] = 1.0f;
			break;
		}
		case BM_SUBTRACT:
		{
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_REVERSE_SUBTRACT;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_REVERSE_SUBTRACT;

			colorBlend.blendConstants[0] = 1.0f;
			colorBlend.blendConstants[1] = 1.0f;
			colorBlend.blendConstants[2] = 1.0f;
			colorBlend.blendConstants[3] = 1.0f;
			break;
		}
		case BM_ADD_QUATER_SOURCE:
		{
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			colorBlend.blendConstants[0] = 64.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[1] = 64.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[2] = 64.0f * (1.0f / 255.0f);
			colorBlend.blendConstants[3] = 64.0f * (1.0f / 255.0f);
			break;
		}
		}

		Emulator_CreatePipelineState(shader, &shader->GP[i], &colorBlend);
	}
}

void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles)
{
	if (triangles <= 0)
		return;

	if (!g_resetDeviceOnNextFrame)
	{
		vkCmdDrawIndexed(commandBuffers[currentFrame], triangles * 3, 1, start_index, 0, 0);
	}
}

void Emulator_UpdateVertexBuffer(const struct Vertex* vertices, int num_vertices, int vertex_start_index, int use_offset)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);

	if (num_vertices <= 0)
		return;

	void* data = NULL;

	if (vkMapMemory(device, dynamic_vertex_buffer_memory, vertex_start_index * sizeof(Vertex), num_vertices * sizeof(Vertex), 0, &data) != VK_SUCCESS)
	{
		eprinterr("Failed to map vertex buffer memory\n");
		assert(FALSE);
	}
	
	if (use_offset)
	{
		vertices += vertex_start_index;
	}

	memcpy(data, vertices, num_vertices * sizeof(Vertex));
	
	vkUnmapMemory(device, dynamic_vertex_buffer_memory);

	VkBuffer vertexBuffers[] = { dynamic_vertex_buffer };
	VkDeviceSize offsets[] = { 0 };

	vkCmdBindVertexBuffers(commandBuffers[currentFrame], 0, 1, vertexBuffers, offsets);

	vbo_was_dirty_flag = TRUE;
}

void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices, int face_start_index, int use_offset)
{
	assert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

	void* data = NULL;

	if (vkMapMemory(device, dynamic_index_buffer_memory, face_start_index * sizeof(unsigned short), num_indices * sizeof(unsigned short), 0, &data) != VK_SUCCESS)
	{
		eprinterr("Failed to map index buffer memory\n");
		assert(FALSE);
	}

	if (use_offset)
	{
		indices += face_start_index;
	}

	memcpy(data, indices, num_indices * sizeof(unsigned short));

	vkUnmapMemory(device, dynamic_index_buffer_memory);

	vkCmdBindIndexBuffer(commandBuffers[currentFrame], dynamic_index_buffer, 0, VK_INDEX_TYPE_UINT16);
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
	float offset_x = (float)activeDispEnv.screen.x;
	float offset_y = (float)activeDispEnv.screen.y;

	memset(&g_viewport, 0, sizeof(VkViewport));

	g_viewport.x = (float)x + offset_x;
	g_viewport.y = (float)y + offset_y + height;
	g_viewport.width = (float)width;
	g_viewport.height = -((float)height);
	g_viewport.minDepth = 0.0f;
	g_viewport.maxDepth = 1.0f;

	if (begin_pass_flag && !g_resetDeviceOnNextFrame)
	{
		vkCmdSetViewport(commandBuffers[currentFrame], 0, 1, &g_viewport);
	}
}

void Emulator_SwapWindow()
{
	unsigned int timer = 1;

#if defined(SINGLE_THREADED)
	Emulator_CounterWrapper(0, &timer);
#endif

	Emulator_WaitForTimestep(1);

	VkPipelineStageFlags waitDestStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	VkResult vkr = vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]);
	if (vkr != VK_SUCCESS)
	{
		eprinterr("Failed to submit queue!\n");
		assert(FALSE);
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	vkQueuePresentKHR(presentQueue, &presentInfo);

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Emulator_WaitForTimestep(int count)
{
	if (g_swapInterval > 0)
	{
		int delta = g_swapTime + FIXED_TIME_STEP * count - Emulator_GetTicks();

		if (delta > 0) {
			SDL_Delay(delta);
		}
	}

	g_swapTime = Emulator_GetTicks();
}

void Emulator_SetRenderTarget(const RenderTargetID& frameBufferObject)
{

}

void Emulator_CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
{
	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
	{
		eprinterr("Failed to create image!\n");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(device, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = Emulator_FindMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate memory!\n");
	}

	vkBindImageMemory(device, image, imageMemory, 0);
}

void Emulator_CreateVulkanRenderPass()
{
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = surfaceFormat.format;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency{};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &render_pass) != VK_SUCCESS)
	{
		eprinterr("Failed to create render pass\n");
		assert(FALSE);
	}
}

void Emulator_DestroyVulkanRenderPass()
{
	vkDestroyRenderPass(device, render_pass, NULL);
	render_pass = VK_NULL_HANDLE;
}

void Emulator_DestroyVulkanFrameBuffers()
{
	for (unsigned int i = 0; i < swapchainImageViews.size(); i++)
	{
		vkDestroyFramebuffer(device, swapchainFramebuffers[i], NULL);
	}
}

#endif