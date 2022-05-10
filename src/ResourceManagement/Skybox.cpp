#include "Skybox.h"
#include "../Helper/JsonHelper.h"
#include "../Helper/TextureHelper.h"
#include <fmt/format.h>
#include <chrono>

float Skybox::getRotation() const
{
	return _rotation;
}

void Skybox::setRotation(float rotation)
{
	_rotation = rotation;
}

void Skybox::loadResourceImpl()
{
	std::string path = fmt::format("resources/skyboxes/{}", _name);
	
	nlohmann::ordered_json root = JsonHelper::loadJsonFromFile(fmt::format("{}/skybox.json", path));
	
	std::string facePaths[6] =
	{
		fmt::format("{}/{}", path, root["right"].get<std::string>()),
		fmt::format("{}/{}", path, root["left"].get<std::string>()),
		fmt::format("{}/{}", path, root["down"].get<std::string>()),
		fmt::format("{}/{}", path, root["up"].get<std::string>()),
		fmt::format("{}/{}", path, root["front"].get<std::string>()),
		fmt::format("{}/{}", path, root["back"].get<std::string>())
	};
	
	std::array<StbImage, 6> data;
	int skyboxComp;
	glm::ivec2 skyboxSize;
	
	bool firstIteration = true;
	for (int i = 0; i < 6; ++i)
	{
		data[i] = StbImage(facePaths[i].c_str());
		
		if (!data[i].isValid())
		{
			throw std::runtime_error(fmt::format("Unable to load image {} from disk", path));
		}
		
		if (firstIteration)
		{
			skyboxComp = data[i].getChannelCount();
			skyboxSize = data[i].getSize();
			firstIteration = false;
		}
		
		if (data[i].getChannelCount() != skyboxComp || data[i].getSize() != skyboxSize)
		{
			throw std::runtime_error(fmt::format("Skybox {} have images with different formats", _name));
		}
	}
	
	TextureProperties textureProperties = TextureHelper::getTextureProperties(COLOR_SRGB);
	
	CubemapCreateInfo createInfo;
	createInfo.size = data[0].getSize();
	createInfo.internalFormat = textureProperties.internalFormat;
	createInfo.textureFiltering = GL_LINEAR;
	createInfo.swizzle = textureProperties.swizzle;
	
	_resource = std::make_unique<Cubemap>(createInfo);
	
	for (int i = 0; i < data.size(); i++)
	{
		PixelProperties pixelProperties = TextureHelper::getPixelProperties(data[i].getChannelCount(), data[i].getBitPerChannel());
		
		_resource->setData(data[i].getPtr(), i, pixelProperties.format, pixelProperties.type);
	}
	
	GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	auto timeout = std::chrono::seconds(10);
	glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, std::chrono::duration_cast<std::chrono::nanoseconds>(timeout).count());
}
