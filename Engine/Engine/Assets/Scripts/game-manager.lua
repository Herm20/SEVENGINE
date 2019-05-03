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
		mesh = "box",
		material = "test"
	},
	script = {
		path = "Assets/Scripts/orbiter.lua"
	}
}

function init(self)
	print("Hello World")
	
	world.spawnentity(lightprefab)
	world.spawnentity(swordprefab)
	--world.spawnentity(orbiterprefab)
    
    self.tt = 0
end

function update(self, dt)
    self.tt = self.tt + dt
    
    camera.setposition({ 0, self.tt, 5 })
end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end
