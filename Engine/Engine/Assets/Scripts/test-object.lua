function init(self)
	print("Hello World")
	
	self.tt = 0
	self.longestframe = 0
end

function update(self, dt)
	self.tt = self.tt + dt
	self.longestframe = math.max(self.longestframe, dt)

	if self.longestframe == dt then print("Longest DT - ", dt) end
	-- print(self.tt, ":", dt)

	local xpos = math.sin(self.tt) * 2
	local zpos = math.cos(self.tt) * 2
	local ypos = 0 -- math.sin(self.tt * 20 / 2) + 3
	local sca = math.sin(self.tt) * 0.5 + 0.75
	
	curpos = entity.getposition()
	
	-- entity.setposition({curpose[1] + xpos, curpos[2], curpos[3] + zpos})
	-- entity.setrotation(math.eulerangles({0, self.tt, 0}))
	-- entity.setscale({sca, sca, sca})
	-- entity.setrotation(math.axisangle({0, 1, 0}, self.tt))
	
	-- print(math.axisangle)
	
	-- entity.rotate(math.axisangle({1, 0, 0}, dt))
	-- local quat = math.axisangle({0, 1, 0}, dt)
	local quat = math.eulerangles({0, dt, 0})
	entity.rotatelocal(quat)
	-- entity.scale({1 + dt, 1 + dt , 1 + dt})
	
	local vv = entity.upvector()
	-- print(vv[1], vv[2], vv[3])
end
