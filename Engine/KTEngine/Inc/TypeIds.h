#pragma once

namespace KTEngine
{
	enum class ComponentId
	{
		Invalid,     //default value
		Transform,   //transform component for location data
		Camera,      //contains a Camera for viewing
		FPSCamera,   // Functionality for a camera to move
		Mesh,        //Create a mesh render object
		Model,		 //creates a model render object
		Animator,	 // manages and controls animations
		Count
	};

	enum class ServiceId
	{
		Invalid,
		Camera,
		Render,
		Count
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
	uint32_t GetTypeId() const override {return StaticGetTypeId();}