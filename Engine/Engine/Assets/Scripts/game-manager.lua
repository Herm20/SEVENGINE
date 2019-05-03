
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
		mesh = "quad",
		material = "spritesheet"
	},
	spritesheet = {
		size = { 175, 175, 0 },
		texture = "NewspiderSheet",
        animations = {
            idle = {
                rate = 0.25,
                startframe = 10,
                endframe = 19,
                loops = true
            },
            walk = {
                rate = 0.15,
                startframe = 20,
                endframe = 31,
                loops = true
            },
            jump = {
                rate = 0.15,
                startframe = 32,
                endframe = 44,
                loops = true
            }
        }
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
		scale = { 0.8, 5.4, 0.1 },
		offset = { 0, 1.5, 0 }
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
		offset = { 0, 0, 0 }
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
		material = "redNoSpecular"
	},
	script = {
		path = "Assets/Scripts/healthbar.lua"
	}
}

local stageprefab = {
	transform = {
		position = { 0, -0.5, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 5, 5, 5 }
	},
	meshrenderer = {
		mesh = "stage",
		material = "test"
	}
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
	world.spawnentity(swordprefab)
    
    self.tt = 0

	world.spawnentity(playerprefab)
	world.spawnentity(playerprefab)

	world.spawnentity(healthbarprefab)
	world.spawnentity(healthbarprefab)

	world.spawnentity(stageprefab)

	--
	--for i, v in pairs(scripts) do
	--	if v.entityid == eid then
	--		sid = i
	--	end
	--end
	--

end

function update(self, dt)
    self.tt = self.tt + dt
end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end
