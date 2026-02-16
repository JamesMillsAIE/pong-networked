#pragma once

#include "Common.h"

/**
 * The base class for any object in the game.
 */
class Actor
{
public:
	Vector2 location; /**< The current location of the actor in world-space. */
	Vector2 size; /**< The size of the entire actor; for circles the magnitude is the diameter. */
	float rotation; /**< The current orientation of the actor in world-space. */
	Color tint; /**< The color of the object when rendering. It can be used to change the tint of a sprite. */

public:
	/**
	 * @param location The initial location of the actor.
	 * @param size The initial size of the actor.
	 * @param rotation The initial orientation of the actor.
	 * @param tint The color of the actor when rendering. It can be used to change the tint of a sprite.
	 */
	Actor(Vector2 location, Vector2 size, float rotation, Color tint);
	virtual ~Actor();

public:
	/** The initialisation function of the actor. */
	virtual void BeginPlay();

	/**
	 * The update function of the actor. Intended to be overridden.
	 * @param dt The frame time calculated by Raylib, passed down through the game.
	 */
	virtual void Tick(float dt);

	/** The function where the actor can draw itself. */
	virtual void Render();

	/** The cleanup function of the actor. */
	virtual void EndPlay();

	/** Returns the bounding box of the actor. Use for physics and rendering. */
	Rectangle Bounds() const;

};