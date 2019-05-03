
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

local player1prefab = {
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
		offset = { 0, 0, 0 }
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
                endframe = 46,
                loops = true
            },
            punch = {
                rate = 0.25,
                startframe = 47,
                endframe = 52,
                loops = true
            },
            uppercut = {
                rate = 0.15,
                startframe = 53,
                endframe = 60,
                loops = true
            },
            kick = {
                rate = 0.15,
                startframe = 60,
                endframe = 64,
                loops = true
            }
        },
        animkey = "punch"
	}
}

local player2prefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "quad",
		material = "spritesheetp2"
	},
	script = {
		path = "Assets/Scripts/player.lua"
	},
	collider = {
		type = "hurtbox",
		shape = "cube",
		offset = { 0, 0, 0 }
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
                endframe = 46,
                loops = true
            },
            punch = {
                rate = 0.25,
                startframe = 47,
                endframe = 52,
                loops = true
            },
            uppercut = {
                rate = 0.15,
                startframe = 53,
                endframe = 60,
                loops = true
            },
            kick = {
                rate = 0.15,
                startframe = 60,
                endframe = 64,
                loops = true
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
		material = "test"
	}
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
    
    self.tt = 0

	world.spawnentity(player1prefab)
	world.spawnentity(player2prefab)

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
