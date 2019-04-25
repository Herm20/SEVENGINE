function init(self)
	print("Hello World")
	
	for k,v in pairs(input.keys) do
		print(k)
	end
	
	self.tt = 0
	self.rot = 0
	self.h = 0
	self.longestframe = 0
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
		entity.setposition({xpos, ypos, zpos})
	end
	
	local epos = entity.getposition()
	entity.setposition({epos[1], self.h, epos[3]})
	
	local quat = math.eulerangles({self.rot, self.tt, 0})
	entity.setrotation(quat)
end
