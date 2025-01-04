local Player = require("player")
local Projectile = require("projectile")
local Util = require("util")

text_font = FontRef.new("Cascadia Code", true, false, false, 62)

bitmaps = {
    player = BitmapRef.new("resources/player.png", true),
    enemy = BitmapRef.new("resources/enemy.png", true),
    projectiles = BitmapRef.new("resources/bullets.png", true),
}

screen_size = Vector2l.new(500, 500)
pixel_scale = 4

player = Player{
    position = Vector2l.new(screen_size.x // 2, 400),
    max_x = screen_size.x - bitmaps.player:get_size().x * pixel_scale,
}

projectiles = {}

--- Configures the application.
--- @param context SetupContext
function setup(context)
    context:set_window_size(screen_size)
    context:set_window_title("Space Invaders")
    context:set_listen_keys(Keys.SPACE .. Keys.ESCAPE)

    Painter.set_font(text_font)
end


--- Handles logic updates.
--- @param delta_time number The time elapsed since the last frame, in seconds.
function update(delta_time)
    for i,proj in pairs(projectiles) do
        if proj ~= nil then
            proj:update_movement()
            -- remove off-screen projectiles
            if proj.position.y < 0 or proj.position.y > screen_size.y then
                projectiles[i] = nil
            end
        end
    end
end


--- Handles drawing.
function draw()
    Painter.fill_window_rect(Colors.BLACK)
    Painter.draw_bitmap_scaled(bitmaps.player, player.position, Vector2l.new(pixel_scale, pixel_scale));

    local player_projectile_top_left = Vector2l.new(6, 0)
    local player_projectile_bottom_right = Vector2l.new(9, 8)

    for i,proj in pairs(projectiles) do
        if proj ~= nil then
            Painter.draw_bitmap_sourced_scaled(
                bitmaps.projectiles, proj.position,
                player_projectile_top_left, player_projectile_bottom_right,
                Vector2l.new(pixel_scale, pixel_scale)
            )
        end
    end
end

--- Called every frame. Check whether continuous keys are pressed here.
function check_keyboard()
    if Engine.is_key_pressed("A") and player.position.x > 0 then
        player:move(-1 * math.tointeger(math.ceil(player.speed * delta_time)))
    end

    if Engine.is_key_pressed("D") and player.position.x < player.max_x then
        player:move(math.tointeger(math.ceil(player.speed * delta_time)))
    end
end


--- Called whenever a key in the listen keys is released.
--- @param key string the released key.
function key_pressed(key)
    if key == Keys.ESCAPE then
        Engine.quit()
    end

    if key == Keys.SPACE then
        local pos = Vector2l.new(player.position.x, player.position.y)
        pos.x = pos.x + (bitmaps.player:get_size().x * pixel_scale // 2) - pixel_scale

        Util.array_nil_insert(projectiles, Projectile{
            position = pos,
            direction = Dir.UP,
            type = Type.PLAYER,
        })
    end
end
