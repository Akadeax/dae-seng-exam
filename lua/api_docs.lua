--- @meta

--- @class SetupContext
--- Context for setting up the application window.
SetupContext = {}

--- Sets the window size.
--- @param width number # The width of the window.
--- @param height number # The height of the window.
--- @return nil
function SetupContext:set_window_size(width, height) end

--- Sets the window title.
--- @param title string # The title of the window.
--- @return nil
function SetupContext:set_window_title(title) end

--- Gets the window title.
--- @return string # The current window title.
function SetupContext:get_window_title() end

--- Gets the window width.
--- @return number # The current window width.
function SetupContext:get_window_width() end

--- Gets the window height.
--- @return number # The current window height.
function SetupContext:get_window_height() end


--- @class Vector2l
--- @field x number The x-component
--- @field y number The y-component
Vector2l = {}

--- @param x number The x-component
--- @param y number The y-component
--- @return Vector2l vec Constructed vector
--- @overload fun(x: integer, y: integer): Vector2l
function Vector2l.new(x, y) end
