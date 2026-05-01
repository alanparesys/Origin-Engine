#pragma once
#include <iostream>
#include "Resources/resources_manager.h"


class Texture : public IResource
{
public:
	Texture();
	~Texture();
	bool Load(const std::string& path) override;
	void Unload();
	unsigned int textureID = 0;
};