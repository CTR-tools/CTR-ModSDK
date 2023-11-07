#ifndef EMULATOR_RENDER_VULKAN_H
#define EMULATOR_RENDER_VULKAN_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#if defined(VULKAN)
struct TextureImage
{
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	VkImageView textureImageView;
};

typedef TextureImage TextureID;

#define MAX_NUM_BLEND_MODES (5)

struct ShaderID
{
	enum ShaderType
	{
		gte_4,
		gte_8,
		gte_16,
		blit,
	};

	enum ShaderType T;
	VkPipelineShaderStageCreateInfo VS;
	VkPipelineShaderStageCreateInfo PS;
	VkDescriptorSetLayout DL;
	VkSampler SS;
	VkSampler SSLUT;
	VkPipeline GP[MAX_NUM_BLEND_MODES];
	VkPipelineLayout PL;
};

typedef void* RenderTargetID;

extern ShaderID* g_shaders[];

extern VkBuffer dynamic_vertex_buffer;

extern VkDeviceMemory dynamic_vertex_buffer_memory;

extern VkDevice device;

extern int Emulator_InitialiseVulkanContext(char* windowName);

extern void Emulator_BeginPass();

extern unsigned int g_vertexBufferMemoryBound;

extern std::vector<VkCommandBuffer> commandBuffers;

extern unsigned int currentFrame;

extern void Emulator_EndPass();

extern int Emulator_BeginCommandBuffer();

extern void Emulator_EndCommandBuffer();

#endif

#endif