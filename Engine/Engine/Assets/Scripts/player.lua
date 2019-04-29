
function init(self)

	if not player1 then
		print("Creating Player 1")
		player1 = self
		entity.setposition({ -2, 0, 0 })
		self.keybinds = {
			left = "j",
			right = "l",
			jump = "i"
		}
	else
		print("Creating Player 2")
		player2 = self
		entity.setposition({ 2, 0, 0 })
		self.keybinds = {
			left = "left",
			right = "right",
			jump = "up"
		}
	end

	self.speed = 3
	self.jumping = false
	self.jumpHeight = 10
	self.yVel = 0

end

function update(self, dt)
	
	-- Move Left/Right
	local xDir = 0
	if input.getkey(input.keys[self.keybinds.right]) then
		xDir = 1
	elseif input.getkey(input.keys[self.keybinds.left]) then
		xDir = -1
	end
	entity.translate({ self.speed * xDir * dt, 0, 0 })

	-- Jumping
	if (not self.jumping) and input.getkeydown(input.keys[self.keybinds.jump]) then
		self.yVel = self.jumpHeight
		self.jumping = true
	end
	self.yVel = self.yVel + GRAVITY * dt

	local pos = entity.getposition()
	if pos[2] + self.yVel * dt < 0 and self.yVel < 0 then
		entity.setposition({ pos[1], 0, pos[3] })
		self.yVel = 0
		self.jumping = false
	end
	entity.translate({ 0, self.yVel * dt, 0 })

end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
end