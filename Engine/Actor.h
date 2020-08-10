#pragma once
#include <Maths.h>
#include <vector>
#include "Transform.h"
#include <string>
#include "Component.h"
#include "RectRenderer.h"
#include "EllipseRenderer.h"
#include "Collider.h"
#include "PhysicsObject.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "TextRenderer.h"
#include "AudioSource.h"
#include "Button.h";

namespace Engine
{
	// All objects in the game are considered actors
	// Actors are assigned components that alter their behaviour in the game.

	/* 
	* --Components--
	* Renderers - Control rendering an object in a specific way
	* PhysicsObject - Introduces an object to the physics engine and allows it to control the objects position.
	* AudioSource - Creates a virtual source of audio within the game that can play audio files.
	* Animation - Controls the sprite of a spriterenderer based on the provided animation sets.
	*/

	class Actor
	{

	private:
		// A list of references to each actor that has been instantiated.
		static std::vector<Actor*> actorList;
		// The list of components added to this object.
		std::vector<Component*> componentList;
		// Updates the actor instance and its components
		void _update();

	public:
		Actor(string name);
		Actor(string name, string tag);
		~Actor();
		// Name and tag for identification **not yet implemented**
		std::string name, tag;
		// The wordly position of the object.
		Transform transform;
		// Returns the list of actor instances
		static std::vector<Actor*> GetActorList();

		static std::vector<Actor*> FindActorsByName(std::string name);
		static Actor* FindActorByName(std::string name);

		static std::vector<Actor*> FindActorsByTag(std::string tag);
		static Actor* FindActorByTag(std::string tag);

		// Functions for adding a component to the actor instance.
		// Returns a pointer to the newly attached component casted to void*.
		template<typename T>
		void* AddComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "typename T must be of type component.");

			Component* c = static_cast<Component*>(new T(this));

			componentList.push_back(c);

			return c;
		}
		template<>
		void* AddComponent<RectRenderer>()
		{
			
			if (GetComponent<Renderer>())
				throw std::runtime_error("Only one renderer is permitted per actor.");
			else
			{
				RectRenderer* renderer = new RectRenderer(this);
				componentList.push_back(renderer);
				return renderer;
			}
			return nullptr;
		}
		template<>
		void* AddComponent<EllipseRenderer>()
		{
			if(GetComponent<Renderer>())
				throw std::runtime_error("Only one renderer is permitted per actor.");

			else
			{
				EllipseRenderer* r = new EllipseRenderer(this, 10,10);
				componentList.push_back(r);
				return r;
			}
			return nullptr;
		}
		template<>
		void* AddComponent<SpriteRenderer>()
		{
			if (GetComponent<Renderer>())
				throw std::runtime_error("Only one renderer is permitted per actor.");
			else
			{
				SpriteRenderer* s = new SpriteRenderer(this);
				componentList.push_back(s);
				return s;
			}
			return nullptr;
		}
		template<>
		void* AddComponent<TextRenderer>()
		{
			if (GetComponent<Renderer>())
				throw std::runtime_error("Only one renderer is permitted per actor.");
			else
			{
				TextRenderer* s = new TextRenderer(this);
				componentList.push_back(s);
				return s;
			}
			return nullptr;
		}
		template<>
		void* AddComponent<PhysicsObject>()
		{
			PhysicsObject* obj = new PhysicsObject(this);
			componentList.push_back(obj);
			return obj;
		}
		template<>
		void* AddComponent <Animation> ()
		{
			if (!GetComponent<SpriteRenderer>())
			{
				throw std::runtime_error("An animation component requires a sprite renderer.");
				return nullptr;
			}
			else if (GetComponent<Animation>())
			{
				throw std::runtime_error("Only one animation component can be added per actor.");
				return nullptr;
			}
			else
			{
				Animation* animation = new Animation(this);
				componentList.push_back(animation);
				return animation;
			}
		}
		template<>
		void* AddComponent<AudioSource>()
		{
			AudioSource* src = new AudioSource(this);
			componentList.push_back(src);
			return src;
		}
		template<>
		void* AddComponent<Button>()
		{
			Button* btn = new Button(this);
			componentList.push_back(btn);
			return btn;
		}
		// Removes the component from the object.
		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "typename T must be of type component.");

			T* c = nullptr;

			unsigned int i;

			for (i = 0; i < componentList.size(); i++)
			{
				c = dynamic_cast<T*>(componentList[i]);
				if (c)
					break;
			}

			if (c)
			{
				componentList.erase(componentList.begin() + i);
				delete c;
			}

		}
		// Gets a component from the actor instance.
		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "typename T must be of type component.");

			T* t = nullptr;

			for (Component* c : componentList)
			{
				t = dynamic_cast<T*>(c);

				if (t)
					break;

			}
			
			return t;
		}
		// Gets a list of components of the same type from the actor instance.
		template<typename T>
		std::vector<T*> GetComponents()
		{
			static_assert(std::is_base_of<Component, T>::value, "typename T must be of type component.");

			std::vector<T*> components;

			T* t;

			for (Component* c : componentList)
			{
				t = dynamic_cast<T*>(c);

				if (t)
				{
					components.push_basck(t);
					t = nullptr;
				}

			}

			return components;
		}
		// Updates all actor instances.
		static void Update();
	};

}