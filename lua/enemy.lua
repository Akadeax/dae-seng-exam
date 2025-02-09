require("class")
Util = require("util")

--- @enum
EnemyDir = { LEFT = {}, RIGHT = {} }

--- @class Enemy
--- @field position Vector2l
--- @field speed integer
--- @field amplitude integer
--- @field down_per_sec integer
--- @field time_between_shots_min number
--- @field time_between_shots_max number
--- @field frequency integer
--- @field _current_time number
--- @field _starting_y integer
--- @field _direction table
--- @field _time_between_shots number
--- @field _current_time_between_shots number
Enemy = Class{
	position = Vector2l.new(),
	speed = 100,
	amplitude = 20,
	frequency = 5,
	down_per_sec = 15,
	time_between_shots_min = 3.0,
	time_between_shots_max = 7.0,

	_current_time = 0.0,
	_center_y = 0,
	_direction = EnemyDir.RIGHT,
	_time_between_shots = 0.0,
	_current_time_between_shots = 0.0,
}

--- @private
function Enemy:_construct()
	self.position = Vector2l.new(0, -16)
	self._center_y = self.position.y

	self._time_between_shots = math.random(self.time_between_shots_min, self.time_between_shots_max)
end

function Enemy:update()
	self._current_time = self._current_time + delta_time
	self:_movement_vertical()
	self:_movement_horizontal()

	self:_update_shooting()
end

--- @private
function Enemy:_movement_vertical()
	self._center_y = self._center_y + self.down_per_sec * delta_time

	local diff_from_center = math.sin(self._current_time * self.frequency) * self.amplitude
	self.position.y = math.tointeger(math.ceil(self._center_y - diff_from_center)) or 0
end

--- @private
function Enemy:_movement_horizontal()
	multi = 1
	if self._direction == EnemyDir.LEFT then multi = -1 end

	local delta = multi * self.speed * delta_time
	self.position.x = math.tointeger(math.floor(self.position.x + delta + 0.5)) or 0

	local x_size = bitmaps.enemy:get_size().x * pixel_scale / 3;
	local max_x = screen_size.x - x_size

	if self.position.x <= 0 then
		self._direction = EnemyDir.RIGHT
	elseif self.position.x >= max_x then
		self._direction = EnemyDir.LEFT
	end
end

--- @param projectiles Projectile[]
--- @return boolean destroySelf
function Enemy:check_collisions(projectiles)
	local size = bitmaps.enemy:get_size()
	size.x = size.x * pixel_scale
	size.y = size.y * pixel_scale

	local half_size = Vector2l.new(size.x // 3 // 2, size.y // 2)
	local local_pos = Vector2l.new(self.position.x + half_size.x, self.position.y + half_size.y)

	local THRESHOLD = 500
	for i,proj in pairs(projectiles) do
		if proj.type == ProjectileType.PLAYER then
			local dist = proj.position:distance2(local_pos)
			if dist < THRESHOLD then
				projectiles[i] = nil
				return true
			end
		end
	end

	return false
end

--- @private
function Enemy:_update_shooting()
	self._current_time_between_shots = self._current_time_between_shots + delta_time

	if self._current_time_between_shots > self._time_between_shots then
		self._current_time_between_shots = 0.0
		self._time_between_shots = math.random(self.time_between_shots_min, self.time_between_shots_max)
		self:_shoot()
	end
end

--- @private
function Enemy:_shoot()
	local size = bitmaps.enemy:get_size()
	size.x = size.x * pixel_scale
	size.y = size.y * pixel_scale

	local half_size = Vector2l.new(size.x // 3 // 2, size.y // 2)
	local local_pos = Vector2l.new(self.position.x + half_size.x, self.position.y + half_size.y)

	Util.array_nil_insert(projectiles, Projectile{
		position = local_pos,
		direction = ProjectileDir.DOWN,
		type = ProjectileType.ENEMY,
		velocity = 200,
	})
end

return Enemy
