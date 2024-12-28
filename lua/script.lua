line_end = Vector2l.new()

test_bitmap = BitmapRef.new("resources/test_image.png", true)
test_font = FontRef.new("Cascadia Code", true, false, false, 62)

--- Configures the application.
--- @param context SetupContext
function setup(context)
    context:set_window_size(Vector2l.new(500, 500))
    context:set_window_title("Game Made in Lua")
    context:set_listen_keys("WASD")

    Painter.set_font(test_font)
end


--- Handles logic updates.
--- @param delta_time number The time elapsed since the last frame, in seconds.
function update(delta_time)

end


--- Handles drawing.
function draw()
    Painter.fill_window_rect(Colors.AQUA)

    Painter.set_color(Colors.BLUE)
    Painter.draw_string("test", Vector2l.new(10, 10))
end


--- Called every frame. Check whether continuous keys are pressed here.
function check_keyboard()
    if (Engine.is_key_pressed("G")) then
        print("pressed g")
    end
end


--- Called whenever a key in the listen keys is released.
--- @param key string the released key.
function key_pressed(key)
    if key == "W" then line_end.y = line_end.y - 30 end
    if key == "A" then line_end.x = line_end.x - 30 end
    if key == "S" then line_end.y = line_end.y + 30 end
    if key == "D" then line_end.x = line_end.x + 30 end
end
