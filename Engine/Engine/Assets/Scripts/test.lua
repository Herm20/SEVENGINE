reloadtime = 0
reloadlongest = 0

function init()
	math.randomseed(os.time())
	print("Hello World")
	tt = 0
	longestframe = 0
end

function update(dt)
	tt = tt + dt
	reloadtime = reloadtime + dt
	longestframe = math.max(longestframe, dt)
	reloadlongest = math.max(reloadlongest, dt)

	if longestframe == dt then print("Longest DT - ", dt) end
	if reloadlongest == dt then print("Longest / RL - ", dt) end
	-- print(tt, ":", reloadtime, ":", dt)

	local xpos = math.sin(tt * 20)
	local zpos = math.cos(tt * 20)
	local ypos = math.sin(tt * 20 / 2) + 3
	setentityposition(xpos, ypos, zpos)
end
