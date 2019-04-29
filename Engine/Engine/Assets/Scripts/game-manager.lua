
GRAVITY = -30

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
		size = { 1, 1, 1 },
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 })
	}
}

local playerprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "sphere",
		material = "test"
	},
	script = {
		path = "Assets/Scripts/player.lua"
	},
	collider = {
		type = "hurtbox",
		shape = "cube",
		size = { 1, 1, 1 },
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 })
	}
}

local healthbarprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "quad",
		material = "test"
	},
	script = {
		path = "Assets/Scripts/healthbar.lua"
	},
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
	world.spawnentity(orbiterprefab)

	world.spawnentity(playerprefab)
	world.spawnentity(playerprefab)

	world.spawnentity(healthbarprefab)
	world.spawnentity(healthbarprefab)
end

function update(self, dt)
end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end
