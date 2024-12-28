--- @meta

do -- Drawing-related bindings

	--- @class Color
	--- @field r number red component.
	--- @field g number green component.
	--- @field b number blue component.
	Color = {}

	--- @param r integer red component.
	--- @param g integer green component.
	--- @param b integer blue component.
	--- @return Color color Constructed color.
	function Color.new(r, g, b) end

	--- Static object for invoking drawing-related functions.
	--- @class Painter
	Painter = {}

	--- Fill the entire window with a color.
	--- @param color Color The color to fill with.
	function Painter.fill_window_rect(color) end

	--- Set the drawing color.
	--- @param color Color The color to switch to.
	function Painter.set_color(color) end

	--- Set the drawing font.
	--- @param font FontRef The font to be drawn in.
	function Painter.set_font(font) end

	--- Draw a line from startPoint to endPoint.
	--- @param startPoint Vector2l Start point.
	--- @param endPoint Vector2l End point.
	function Painter.draw_line(startPoint, endPoint) end

	--- Draw a hollow rect.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	function Painter.draw_rect(topLeft, bottomRight) end

	--- Draw a filled rect.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	--- @param opacity integer Opacity value from 0-255.
	function Painter.fill_rect(topLeft, bottomRight, opacity) end

	--- Draw a filled rounded rect.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	--- @param radius integer The radius the rect should be rounded by.
	function Painter.draw_filled_rect(topLeft, bottomRight, radius) end

	--- Draw an Oval.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	function Painter.draw_oval(topLeft, bottomRight) end

	--- Draw a filled oval.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	--- @param opacity integer Opacity value from 0-255.
	function Painter.fill_oval(topLeft, bottomRight, opacity) end

	--- Draw an Arc.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	--- @param startDegree integer
	--- @param angle integer
	function Painter.draw_arc(topLeft, bottomRight, startDegree, angle) end

	--- Draw a filled Arc.
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	--- @param startDegree integer
	--- @param angle integer
	--- @param opacity integer Opacity value from 0-255.
	function Painter.fill_arc(topLeft, bottomRight, startDegree, angle, opacity) end

	--- Draw a piece of text at the given position.
	--- @param text string The text to draw
	--- @param topLeft Vector2l The top left coordinates to draw from.
	function Painter.draw_string(text, topLeft) end

	--- Draw a piece of text into the given rect.
	--- @param text string The text to draw
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param bottomRight Vector2l The bottom right coordinates to draw to.
	function Painter.draw_string_sized(text, topLeft, bottomRight) end

	--- Draw a polygon.
	--- @param points table The list of points that form the polygon.
	--- @param close boolean Whether the polygon should be closed.
	function Painter.draw_polygon(points, close) end

	--- Draw a polygon.
	--- @param points table The list of points that form the polygon.
	--- @param close boolean Whether the polygon should be closed.
	function Painter.fill_polygon(points, close) end

	--- Draw a Bitmap.
	--- @param bitmap BitmapRef
	--- @param topLeft Vector2l The top left coordinates to draw from.
	function Painter.draw_bitmap(bitmap, topLeft) end

	--- Draw a Bitmap with a specified source rect.
	--- @param bitmap BitmapRef
	--- @param topLeft Vector2l The top left coordinates to draw from.
	--- @param sourceTopLeft Vector2l The top left coordinates in the source image to draw.
	--- @param sourceBottomRight Vector2l The bottom right coordinates in the source image to draw.
	function Painter.draw_bitmap_sourced(bitmap, topLeft, sourceTopLeft, sourceBottomRight) end

	--- @class BitmapRef
	BitmapRef = {}

	--- Construct a bitmap located at a file path.
	--- @param path string The file path.
	--- @param createAlphaChannel boolean Whether an alpha channel should be created on initialization.
	--- @return BitmapRef bitmap The constructed bitmap.
	function BitmapRef.new(path, createAlphaChannel) end


	--- @class FontRef
	FontRef = {}

	--- Construct a bitmap located at a file path.
	--- @param fontName string Name of the font.
	--- @param bold boolean
	--- @param italic boolean
	--- @param underline boolean
	--- @param size integer Point size.
	--- @return FontRef font The constructed font reference.
	function FontRef.new(fontName, bold, italic, underline, size) end

	--- Provides access to commonly used color constants
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

end



do -- Setup Context

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

end



do -- Engine bindings
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

	--- Static object for invoking engine functions.
	--- @class Engine
	Engine = {}

	--- Check if the given key is pressed.
	--- @param key string the key to check
	function Engine.is_key_pressed(key) end

	--- Quit the Game.
	function Engine.Quit() end

	--- Go into Fullscreen mode.
	function Engine.go_fullscreen() end

	--- Go into windowed mode.
	function Engine.go_windowed() end

end
