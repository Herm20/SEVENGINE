local testspawn = {
	transform = {
		position = { 2, 0, 0 },
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
	
	self.tt = 0
	self.rot = 0
	self.h = 0
	self.longestframe = 0
	
	self.destroyedentity = false
	
	print(world.spawnentity(testspawn))
end

function update(self, dt)
	self.longestframe = math.max(self.longestframe, dt)

	if self.longestframe == dt then print("Longest DT - ", dt) end
	-- print(self.tt, ":", dt)
	
	if input.getkey(input.keys["leftshift"]) then
		dt = dt * 2
	end
	
	if input.getkey(input.keys["kp6"]) then
		self.tt = self.tt + dt
	elseif input.getkey(input.keys["kp4"]) then
		self.tt = self.tt - dt
	end
	
	if input.getkey(input.keys["t"]) then
		self.rot = self.rot - dt
	elseif input.getkey(input.keys["b"]) then
		self.rot = self.rot + dt
	end
	
	if input.getkey(input.keys["kp8"]) then
		self.h = self.h + dt
	elseif input.getkey(input.keys["kp2"]) then
		self.h = self.h - dt
	end

	if (self.tt / math.pi / 2) % 2 <= 1 then
		local xpos = math.sin(self.tt) * 2
		local zpos = math.cos(self.tt) * 2
		local ypos = 0 -- math.sin(self.tt * 20 / 2) + 3
		-- entity.setposition({xpos, ypos, zpos})
	end
	
	local epos = entity.getposition()
	entity.setposition({epos[1], self.h, epos[3]})
	
	local quat = math.eulerangles({self.rot, self.tt, 0})
	-- entity.setrotation(quat)
	
	self.tt = self.tt + dt
		
	for i, v in ipairs(scripts) do
		if not (v.scriptid == self.scriptid) then
			world.sendmessage(v.entityid, v.scriptid, "Hello", self.scriptid)
		end
	end
	
	if self.tt > 2 and not self.destroyedentity then
		-- world.destroyentity(1)
		self.destroyedentity = true
	end
end

function onmessage(self, message, data)
	-- print("I'm script #" .. tostring(self.scriptid))
	-- print(message, type(data), data, data.val)
	-- print("Hello from script #" .. tostring(data))
	-- print("--------------------")
end
