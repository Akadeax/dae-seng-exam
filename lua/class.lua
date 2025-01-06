-- Class functions as a simulation for OOP structures via metatables.
-- This allows for base classes and instantiating a class via ClassName().
-- for Examples on usage see player/projectile/enemy.lua.
function Class(base)
	local cls = base or {}
	cls.__index = cls
	function cls:new(o)
	  o = o or {}
	  setmetatable(o, cls)

	  -- Let classes define a construct method
	  if cls._construct then
		o:_construct()
	  end

	  return o
	end

	setmetatable(cls, {
	  __call = function(_, ...)
		return cls:new(...)
	  end,
	})

	return cls
end

return Class
