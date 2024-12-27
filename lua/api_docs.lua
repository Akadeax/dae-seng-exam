--- @meta

--- @class SetupContext
--- Context for setting up the application window.
SetupContext = {}

--- Gets the window size.
--- @return Vector2l size The current window size.
function SetupContext:get_window_size() end

--- Sets the window size.
--- @param vecSize Vector2l The size of the window.
function SetupContext:set_window_size(vecSize) end


--- Gets the window title.
--- @return string title The current window title.
function SetupContext:get_window_title() end

--- Sets the window title.
--- @param title string The title of the window.
function SetupContext:set_window_title(title) end


--- Gets the listen keys.
--- @return string listen_keys the listen keys.
function SetupContext:get_listen_keys() end

--- Sets the listen keys.
--- @param keys string The listen keys.
function SetupContext:set_listen_keys(keys) end



--- @class Vector2l
--- @field x number The x-component.
--- @field y number The y-component.
Vector2l = {}

--- @param x integer The x-component.
--- @param y integer The y-component.
--- @return Vector2l vec Constructed vector.
function Vector2l.new(x, y) end

--- @return Vector2l vec Constructor zero vector.
function Vector2l.new() end

--- Prints the vector to console.
function Vector2l.print() end


--- @class Color
--- @field r number red component.
--- @field g number green component.
--- @field b number blue component.
--- @field RED Color
Color = {}

--- @param r integer red component.
--- @param g integer green component.
--- @param b integer blue component.
--- @return Color color Constructed color.
function Color.new(r, g, b) end


--- @class Colors
--- @field BLACK Color
--- @field WHITE Color
--- @field RED Color
--- @field GREEN Color
--- @field BLUE Color
--- @field YELLOW Color
--- @field CYAN Color
--- @field MAGENTA Color
--- @field GRAY Color
--- @field LIGHT_GRAY Color
--- @field DARK_GRAY Color
--- @field ORANGE Color
--- @field PINK Color
--- @field PURPLE Color
--- @field BROWN Color
--- @field LIME Color
--- @field OLIVE Color
--- @field MAROON Color
--- @field NAVY Color
--- @field TEAL Color
--- @field GOLD Color
--- @field SILVER Color
--- @field BEIGE Color
--- @field TURQUOISE Color
--- @field INDIGO Color
--- @field VIOLET Color
--- @field SALMON Color
--- @field CORAL Color
--- @field CHOCOLATE Color
--- @field KHAKI Color
--- @field PLUM Color
--- @field TAN Color
--- @field AQUA Color
--- @field FUCHSIA Color
--- @field SEA_GREEN Color
--- @field LAVENDER Color
--- @field CRIMSON Color
--- @field MINT Color
--- @field SKY_BLUE Color
--- @field PEACH Color
Colors = {}

--- @class Painter
--- Static object for invoking drawing-related functions.
Painter = {}

--- Fill the entire window with a color.
--- @param color Color the color to fill with.
function Painter.fill_window_rect(color) end

--- Set the drawing color.
--- @param color Color the color to switch to.
function Painter.set_color(color) end

--- Draw a line from startPoint to endPoint.
--- @param startPoint Vector2l start point.
--- @param endPoint Vector2l end point.
function Painter.draw_line(startPoint, endPoint) end
