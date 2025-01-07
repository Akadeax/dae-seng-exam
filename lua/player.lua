require("class")

--- @class Player
--- @field position Vector2l
--- @field speed number
--- @field max_x integer
--- @field max_overheat number
--- @field overheat_per_shot number
--- @field overheat_decay_per_second number
--- @field _current_overheat number
Player = Class{
	position = Vector2l.new(),
	speed = 200,
	max_x = 0,
	max_overheat = 100.0,
	overheat_per_shot = 10.0,
	overheat_decay_per_second = 20.0,

	_current_overheat = 0.0,
}

function Player:move(delta)
	self.position.x = self.position.x + delta
end

function Player:update()
	if self._current_overheat > 0 then
		self._current_overheat = self._current_overheat - delta_time * self.overheat_decay_per_second

		if self._current_overheat <= 0 then
			self._current_overheat = 0
		end
	end
end


--- @param projectiles Projectile[]
--- @return boolean destroySelf
function Player:check_collisions(projectiles)
	local size = bitmaps.player:get_size()
	size.x = size.x * pixel_scale
	size.y = size.y * pixel_scale

	local half_size = Vector2l.new(size.x // 2, size.y // 2)
	local local_pos = Vector2l.new(self.position.x + half_size.x, self.position.y + half_size.y)

	local THRESHOLD = 625
	for i,proj in pairs(projectiles) do
		if proj.type == ProjectileType.ENEMY then
			local dist = proj.position:distance2(local_pos)
			if dist < THRESHOLD then
				projectiles[i] = nil
				return true
			end
		end
	end

	return false
end

function Player:try_shoot()
	if (self._current_overheat + self.overheat_per_shot) > self.max_overheat then
		return
	end

	self._current_overheat = self._current_overheat + self.overheat_per_shot

	local pos = Vector2l.new(self.position.x, self.position.y)
	pos.x = pos.x + (bitmaps.player:get_size().x * pixel_scale // 2) - pixel_scale

	Util.array_nil_insert(projectiles, Projectile{
		position = pos,
		direction = ProjectileDir.UP,
		type = ProjectileType.PLAYER,
	})
end

return Player
