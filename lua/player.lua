require("class")

--- @class Player
--- @field position Vector2l
--- @field speed number
--- @field max_x integer
Player = Class{
	position = Vector2l.new(),
	speed = 200,
	max_x = 0,
}

function Player:move(delta)
	self.position.x = self.position.x + delta
end

return Player
