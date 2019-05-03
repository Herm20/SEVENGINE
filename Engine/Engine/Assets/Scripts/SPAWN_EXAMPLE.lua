{
	transform = {
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 }),
		scale    = { 1, 1, 1 }
	},
	meshrenderer = {
		mesh = "box",
		material = "test"
	},
	rigidbody = {
		velocity = { 0, 0, 0 }
	},
	light = {
		position = { 0, 0, 0 },
		direction = { 0, 0, 1 },
		color = { 0, 0, 0 },
		radius,
		intensity = { 0, 0, 0 },
	},
	collider = {
		type = "hitbox",
		shape = "cube",
		size = { 1, 1, 1 },
		position = { 0, 0, 0 },
		rotation = math.eulerangles({ 0, 0, 0 })
	},
	script = {
		path = "Assets/Scripts/orbiter.lua"
	}
}