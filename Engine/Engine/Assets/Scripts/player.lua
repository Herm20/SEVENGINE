
local punchprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	collider = {
		type = "hitbox",
		shape = "cube",
		scale = { 0.2, 0.2, 0.1 },
		offset = { 0.82, -0.2, 0 }
	},
	meshrenderer = {
		mesh = "none",
		material = "test"
	}
}

local uppercutprefab = {
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	collider = {
		type = "hitbox",
		shape = "cube",
		scale = { 0.2, 0.4, 0.1 },
		offset = { 0.82, 0, 0 }
	},
	meshrenderer = {
		mesh = "none",
		material = "test"
	}
}

function init(self)

	if not player1 then
		print("Creating Player 1")
		player1 = self
		entity.setposition({ -2, 0, 0 })
		self.facingright = true
		self.keybinds = {
			left = "a",
			right = "d",
			jump = "w",
			punch = "t"
		}
	else
		print("Creating Player 2")
		player2 = self
		entity.setposition({ 2, 0, 0 })
		self.facingright = false
		self.keybinds = {
			left = "left",
			right = "right",
			jump = "up",
			punch = "period"
		}
	end

	self.speed = 3
	self.jumpHeight = 10
	self.yVel = 0
	self.state = "JUMP"
	
	self.position = {0, 0, 0}

	self.maxhealth = 100
	self.health = self.maxhealth
	self.tt = 0

	self.attackstringcount = 0
	self.hitboxlifetime = 0
	self.hitboxid = -1

end

function update(self, dt)

	-- Move Left/Right
	if (not (self.state == "ATTACK")) then
		local xDir = 0
		if input.getkey(input.keys[self.keybinds.right]) then
			xDir = 1
		elseif input.getkey(input.keys[self.keybinds.left]) then
			xDir = -1
		end
		entity.translate({ self.speed * xDir * dt, 0, 0 })
		if not (self.state == "JUMP") then
			if xDir == 0 then
				entity.setanimkey({"idle"})
			else
				entity.setanimkey({"walk"})
			end
		end
	end

	-- Jumping
	if (not (self.state == "JUMP")) and (not (self.state == "ATTACK")) and input.getkeydown(input.keys[self.keybinds.jump]) then
		self.yVel = self.jumpHeight
		self.state = "JUMP"
        entity.setanimkey({"jump"});
        entity.playeffect({"Assets/Audio/Effects/jump.mp3"});
	end
	self.yVel = self.yVel + GRAVITY * dt

	local pos = entity.getposition()
	if pos[2] + self.yVel * dt < 0 and self.yVel < 0 then
		entity.setposition({ pos[1], 0, pos[3] })
		self.yVel = 0
		if self.state == "JUMP" then
			self.attackstringcount = 0
            entity.setanimkey({"idle"});
			self.state = "GROUND"
		end
	end
	entity.translate({ 0, self.yVel * dt, 0 })

	-- Update position for use by other scripts
	self.position = entity.getposition()
	if player1 == self then
		facingright = (self.position[1] < player2.position[1])
	else
		facingright = (self.position[1] < player1.position[1])
	end

	-- Attacking
	if self.state == "ATTACK" then
		self.hitboxlifetime = self.hitboxlifetime - dt
		if self.hitboxlifetime < 0  and not (self.hitboxid == -1) then
			world.destroyentity(self.hitboxid)
			if self.attackstringcount == 2 then
				entity.setanimkey({"uppercut"});
                entity.playeffect({"Assets/Audio/Effects/uppercut.mp3"});
				uppercutprefab.transform.position = self.position
				if not facingright then
					uppercutprefab.collider.offset[1] = -math.abs(uppercutprefab.collider.offset[1])
				else
					uppercutprefab.collider.offset[1] = math.abs(uppercutprefab.collider.offset[1])
				end
				self.hitboxid = world.spawnentity(uppercutprefab)
				self.hitboxlifetime = 0.2
				self.attackstringcount = 3
			else
				self.state = "GROUND"
			end
		end
	end

	if (self.state == "JUMP" and not (self.attackstringcount == 4) and input.getkeydown(input.keys[self.keybinds.punch])) then
		self.attackstringcount = 4
		entity.setanimkey({"kick"})
        entity.playeffect({"Assets/Audio/Effects/kick.mp3"});
	end

	if (self.state == "ATTACK" and self.attackstringcount == 1 and input.getkeydown(input.keys[self.keybinds.punch])) then
		self.attackstringcount = 2
	end

	if (not (self.state == "JUMP")) and (not (self.state == "ATTACK")) and input.getkeydown(input.keys[self.keybinds.punch]) then
		self.state = "ATTACK"
       	entity.setanimkey({"punch"});
        entity.playeffect({"Assets/Audio/Effects/punch.mp3"});
		punchprefab.transform.position = self.position
		if not facingright then
			punchprefab.collider.offset[1] = -math.abs(punchprefab.collider.offset[1])
		else
			punchprefab.collider.offset[1] = math.abs(punchprefab.collider.offset[1])
		end
		self.hitboxid = world.spawnentity(punchprefab)
		self.hitboxlifetime = 0.2
		self.attackstringcount = 1
	end

	if self == player then
		print(self.state)
	end

end

function onmessage(self, message, data)
	print("Script #" .. tostring(self.scriptid) .. " received message : " .. message)
	if message == "oncollisionhurtbox" then
		self.health = self.health - 10
		self.health = math.max(0, self.health)
		if self.health <= 0 then
			world.destroyentity(self.worldid)
		end
	end
end