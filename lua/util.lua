local Util = {}

--- Inserts element into the first nil value in the array, or appends it to the end if there is no nil.
--- @param array table
--- @param element any
function Util.array_nil_insert(array, element)
	for i=1, #array, 1 do
		if array[i] == nil then
			array[i] = element
			return
		end
	end

	array[#array + 1] = element
end

--- Turn an entire table into a string.
--- @param table table
--- @return string as_string
function Util.dump(table)
	if type(table) == 'table' then
	   local s = '{ '
	   for key, value in pairs(table) do
		  if type(key) ~= 'number' then key = '"'..key..'"' end
		  s = s .. '['..key..'] = ' .. Util.dump(value) .. ','
	   end
	   return s .. '} '
	else
	   return tostring(table)
	end
 end

return Util
