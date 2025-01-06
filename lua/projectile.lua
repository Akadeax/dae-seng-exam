require("class")

--- @enum
ProjectileDir = { UP = {}, DOWN = {} }
--- @enum
Type = { PLAYER = {}, ENEMY = {} }

--- @class Projectile
--- @field position Vector2l
--- @field direction table
--- @field velocity integer
--- @field type table
Projectile = Class{
	position = Vector2l.new(),
	direction = ProjectileDir.UP,
	velocity = 800,
	type = Type.PLAYER
}

function Projectile:update_movement()
	multi = 1
	if self.direction == ProjectileDir.UP then multi = -1 end

	local delta = multi * self.velocity
	self.position.y = self.position.y + math.tointeger(math.floor(delta * delta_time + 0.5))
end

return Projectile
