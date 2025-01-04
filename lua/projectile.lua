require("class")

Dir = { UP = {}, DOWN = {} }
Type = { PLAYER = {}, ENEMY = {} }

Projectile = Class{
	position = Vector2l.new(),
	direction = Dir.UP,
	velocity = 800
}

function Projectile:update_movement()
	multi = 1
	if self.direction == Dir.UP then multi = -1 end

	self.position.y = self.position.y + math.tointeger(math.ceil(multi * self.velocity * delta_time))
	-- self.position.y = self.position.y + math.tointeger(math.ceil(multi * self.velocity * delta_time))
end

return Projectile
