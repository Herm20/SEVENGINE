# SEVENGINE Lua API Reference

## Lua Resources

Lua scripting within SEVENGINE is based on the LuaJIT Lua engine, which itself is based on Lua 5.1.

There is a wealth of information around for learning the ins and outs of Lua; I personally recommend **Programming in Lua** and the **Lua 5.1 Reference Manual** :

https://www.lua.org/pil/contents.html

www.lua.org/manual/5.1/manual.html

## Engine Specific Data

* `vector` - A table with indices 1,2,3 representing the x,y,z aspects of a 3D vector

* `quaternion` - A table with indices 1,2,3,4 representing the x,y,z,w aspects of a quaternion

## Libraries

### Core Libraries

The core Lua libraries remain unrestricted within SEVENGINE Lua scripts, however may have some functionality added into them by the engine.

### Math

SEVENGINE adds a small amount of functionality to the core Lua `math` library for interacting with core engine components :

* `math.axisangle` - Takes a vector and a number, and returns the quaternion rotation representing the rotation about an axis

* `math.eulerangles` - Takes a vector, and returns the quaternion rotation representing the Euler angles rotation

### Input

The SEVENGINE Lua scripting API offers simple access to player input :

* `input.keys` - A simple map; index with the string representing the desired character - maps to key ID (number)

* `input.getkey` - Takes a key ID (number), and returns a boolean representing whether that key is currently down

### World

The SEVENGINE Lua scripting API offers functionality for interacting with the rest of the game world through its `world` library :

* `world.sendmessage` - Takes the target entity ID, target script ID, message (string), and data (any type), and sends the message with additional data to the specified script

* `world.spawnentity` - Takes an entity descriptor table (see `SPAWN_EXAMPLE.lua` for format example), and spawns an entity, returning the spawned entity's ID

* `world.destroyentity` - Takes an entity ID (number) and destroys the entity

### Entity

The SEVENGINE Lua scripting API contains all Entity-interfacing functionality within the `entity` library :

* `entity.getposition` - Returns the host entity's position as a vector

* `entity.getrotation` - Returns the host entity's rotation as a quaternion

* `entity.getscale` - Returns the host entity's scale as a vector

* `entity.setposition` - Takes a vector, and sets the host entity's position to it

* `entity.setrotation` - Takes a quaternion, and sets the host entity's rotation to it

* `entity.setscale` - Takes a vector, and sets the host entity's scale to it

* `entity.forwardvector` - Returns the host entity's forward vector

* `entity.rightvector` - Returns the host entity's right vector

* `entity.upvector` - Returns the host entity's up vector

* `entity.translate` - Takes a vector, and translates the host entity's position by it

* `entity.translatelocal` - Takes a vector, and translates the host entity's position by it, local to the host entity's rotation

* `entity.rotate` - Takes a quaternion, and rotates the host entity's rotation by it

* `entity.rotatelocal` - Takes a quaternion, and rotates the host entity's rotation by it, about its own local axes

* `entity.scale` - Takes a vector, and multiplies the host entity's scale by it

* `entity.scaleadd` - Takes a vector, and adds it to the host entity's scale
