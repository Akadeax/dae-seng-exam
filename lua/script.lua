text_font = FontRef.new("Cascadia Code", true, false, false, 62)

bitmaps = {
    player = BitmapRef.new("resources/player.png", true),
    enemy = BitmapRef.new("resources/enemy.png", true),
    bullets = BitmapRef.new("resources/bullets.png", true),
}

screen_size = Vector2l.new(500, 500)
pixel_scale = 4
player_position = Vector2l.new(screen_size.x // 2, 400)
player_speed = 200

player_max_x = screen_size.x - bitmaps.player:get_size().x * pixel_scale

--- Configures the application.
--- @param context SetupContext
function setup(context)
    context:set_window_size(screen_size)
    context:set_window_title("Space Invaders")
    context:set_listen_keys("G")

    Painter.set_font(text_font)
end


--- Handles logic updates.
--- @param delta_time number The time elapsed since the last frame, in seconds.
function update(delta_time) end


--- Handles drawing.
function draw()
    Painter.fill_window_rect(Colors.BLACK)
    Painter.draw_bitmap_scaled(bitmaps.player, player_position, Vector2l.new(pixel_scale, pixel_scale));
end


--- Called every frame. Check whether continuous keys are pressed here.
function check_keyboard()
    if Engine.is_key_pressed("A") and player_position.x > 0 then
        player_position.x = player_position.x - math.tointeger(math.ceil(player_speed * delta_time))
        -- player_position.x = player_position.x - (player_speed * delta_time);
    end

    if Engine.is_key_pressed("D") and player_position.x < player_max_x then
        player_position.x = player_position.x + math.tointeger(math.ceil(player_speed * delta_time))
    end
end


--- Called whenever a key in the listen keys is released.
--- @param key string the released key.
function key_pressed(key)
    if key == "G" then
        print("Shoot")
    end
end
