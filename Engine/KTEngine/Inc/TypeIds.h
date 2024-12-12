#pragma once

namespace KTEngine
{
	enum class ComponentId
	{
		Invalid,     //default value
		Transform,   //transform component for location data
		Camera,      //contains a Camera for viewing
		FPSCamera,   // Functionality for a camera to move
		ThirdPersonCamera,
		PlayerController,
		Mesh,        //Create a mesh render object
		Model,		 //creates a model render object
		Animator,	// manages and controls animations
		RigidBody,  //physics object that gets added to the physics world
		SoundEffect, //adds a single sound effect to an object
		SoundBank,   //adds an array of sound effects to an object
		UIText,		//adds a text UI component
		UISprite,   //adds a sprite to the UI
		UIButton,	//adds a button to the UI
		Count
	};

	enum class ServiceId
	{
		Invalid,
		Camera,
		Render,
		Physics,
		UIRender,
		Count
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
	uint32_t GetTypeId() const override {return StaticGetTypeId();}