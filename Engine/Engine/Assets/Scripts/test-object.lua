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

	local xpos = math.sin(self.tt * 20)
	local zpos = math.cos(self.tt * 20)
	local ypos = math.sin(self.tt * 20 / 2) + 3
	setentityposition(xpos, ypos, zpos)
end
