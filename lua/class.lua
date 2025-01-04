function Class(base)
	local cls = base or {}
	cls.__index = cls
	function cls:new(o)
	  o = o or {}
	  setmetatable(o, cls)
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
