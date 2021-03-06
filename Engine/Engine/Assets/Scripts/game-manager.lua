
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

local playerprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "quad",
		material = "spritesheetp1"
	},
	script = {
		path = "Assets/Scripts/player.lua"
	},
	collider = {
		type = "hurtbox",
		shape = "cube",
		offset = { 0.1, -0.3, 0 },
		scale = { 0.5, 0.5, 0.5 }
	},
	spritesheet = {
		size = { 175, 175, 0 },
		texture = "NewspiderSheet",
        animations = {
            idle = {
                rate = 0.0333,
                startframe = 10,
                endframe = 19,
                loops = true
            },
            walk = {
                rate = 0.0333,
                startframe = 20,
                endframe = 31,
                loops = true
            },
            jump = {
                rate = 0.0333,
                startframe = 32,
                endframe = 46,
                loops = false
            },
            punch = {
                rate = 0.0333,
                startframe = 47,
                endframe = 52,
                loops = false
            },
            uppercut = {
                rate = 0.0333,
                startframe = 53,
                endframe = 60,
                loops = false
            },
            kick = {
                rate = 0.0333,
                startframe = 60,
                endframe = 64,
                loops = false
            }
        },
        animkey = "idle"
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
		material = "stage"
	}
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
    
    self.tt = 0

	playerprefab.meshrenderer.material = "spritesheetp1"
	playerprefab.spritesheet.animkey = "uppercut"
	local player1id = world.spawnentity(playerprefab)

	playerprefab.meshrenderer.material = "spritesheetp2"
	playerprefab.spritesheet.animkey = "kick"
	world.spawnentity(playerprefab)
	local player2id = world.spawnentity(playerprefab)

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
