require("class")

Player = Class{
	position = Vector2l.new(),
	speed = 200,
	max_x = 0,
	scale = 4,
}

function Player:move(delta)
	self.position.x = self.position.x + delta
end

return Player
