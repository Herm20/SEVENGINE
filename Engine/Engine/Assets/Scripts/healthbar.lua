
local MAX_SCALE = { 0.8, 0.1, 1 }

function init(self)

	if not healthbar1 then
		healthbar1 = self
		self.player = player1
		print(player1)
	else
		healthbar2 = self
		self.player = player2
	end

	entity.setscale(MAX_SCALE)

end

function update(self, dt)

	local pos = self.player.position
	pos[2] = pos[2] + 1.2
	entity.setposition(pos)

	local frac = self.player.health / self.player.maxhealth
	local scalex = MAX_SCALE[1] * frac
	entity.setscale({ scalex, MAX_SCALE[2], MAX_SCALE[3] })

end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end