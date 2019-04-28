local lightprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, math.pi, 0 }),
		scale    = { 1, 1, 1 }
	},
	light = {
		position = { 0, 0, 0 },
		direction = { 0, 0, 1 },
		color = { 1, 1, 1 },
		radius = 1,
		intensity = 1
	}
}

local swordprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "sword",
		material = "test"
	}
}

local orbiterprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "sword",
		material = "test"
	},
	script = {
		path = "Assets/Scripts/orbiter.lua"
	},
	collider = {
		type = "hitbox",
		shape = "cube",
		size = { 0.6, 3, 0.3 },
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 })
	}
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
	world.spawnentity(swordprefab)
	world.spawnentity(orbiterprefab)
end

function update(self, dt)
end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end
