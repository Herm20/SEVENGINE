function init(self)
	print("Hello World, I'm an Orbiter")
	self.tt = 0
end

function update(self, dt)
	self.tt = self.tt + dt

	local xpos = math.sin(self.tt) * 2
	local zpos = math.cos(self.tt) * 2
	entity.setposition({ xpos, 0, zpos })
	
	local quat = math.eulerangles({ 0, self.tt, 0 })
	entity.setrotation(quat)
	
	local epos = entity.getposition()
end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end