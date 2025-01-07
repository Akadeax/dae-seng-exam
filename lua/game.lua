local Player = require("player")
local Projectile = require("projectile")
local Util = require("util")
local Enemy = require("enemy")

bitmaps = {
    player = BitmapRef.new("resources/player.png", true),
    enemy = BitmapRef.new("resources/enemy.png", true),
    projectiles = BitmapRef.new("resources/bullets.png", true),
} --- @type BitmapRef[]

screen_size = Vector2l.new(500, 500) --- @type Vector2l
pixel_scale = 4 --- @type integer

--- @type Player
player = Player{
    position = Vector2l.new(screen_size.x // 2, 400),
    max_x = screen_size.x - bitmaps.player:get_size().x * pixel_scale,
    scale = pixel_scale,
}

projectiles = {} --- @type Projectile[]
enemies = {} --- @type Enemy[]

--- Configures the application.
--- @param context SetupContext
function setup(context)
    context:set_window_size(screen_size)
    context:set_window_title("Space Invaders")
    context:set_listen_keys(Keys.SPACE .. Keys.ESCAPE)

    Painter.set_font(FontRef.new("Cascadia Code", true, false, false, 62))

    spawn_initial_enemies()
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

    for i,enemy in pairs(enemies) do
        if enemy ~= nil then
            enemy:update()

            if enemy:check_collisions(projectiles) then
                enemies[i] = nil
            end
        end
    end

    player:update()
    if player:check_collisions(projectiles) then
        Engine.quit()
    end
end


function spawn_initial_enemies()
    Engine.make_timer(1.0, function()
        Util.array_nil_insert(enemies, Enemy{ position = Vector2l.new() })
    end, true)
end

--- Handles drawing.
function draw()
    Painter.fill_window_rect(Colors.DARK_GRAY)
    Painter.draw_bitmap_scaled(bitmaps.player, player.position, Vector2l.new(pixel_scale, pixel_scale));

	-- Draw player UI
	local filled_amount = player._current_overheat / player.max_overheat
	local total_fill_height = 100
	local total_fill_width = 30
	local fill_height = math.tointeger(math.floor(total_fill_height * filled_amount)) or 0

	Painter.set_color(Colors.BLACK)
	Painter.fill_rect(Vector2l.new(screen_size.x - total_fill_width, screen_size.y - total_fill_height), screen_size, 255)
	Painter.set_color(Colors.RED)
	Painter.fill_rect(Vector2l.new(screen_size.x - total_fill_width, screen_size.y - fill_height), screen_size, 255)


	-- Draw projectiles
    local player_projectile_top_left = Vector2l.new(6, 0)
    local player_projectile_bottom_right = Vector2l.new(9, 8)

    local enemy_projectile_top_left = Vector2l.new(0, 0)
    local enemy_projectile_bottom_right = Vector2l.new(3, 8)

    for i,proj in pairs(projectiles) do
        if proj ~= nil then
            if proj.type == ProjectileType.PLAYER then
                Painter.draw_bitmap_sourced_scaled(
                    bitmaps.projectiles, proj.position,
                    player_projectile_top_left, player_projectile_bottom_right,
                    Vector2l.new(pixel_scale, pixel_scale)
                )
            else
                Painter.draw_bitmap_sourced_scaled(
                    bitmaps.projectiles, proj.position,
                    enemy_projectile_top_left, enemy_projectile_bottom_right,
                    Vector2l.new(pixel_scale, pixel_scale)
                )
            end
        end
    end

    local enemy_top_left = Vector2l.new(0, 0)
    local enemy_bottom_right = Vector2l.new(11, 8)

    for i,enemy in pairs(enemies) do
        if enemy ~= nil then
            Painter.draw_bitmap_sourced_scaled(
                bitmaps.enemy,
                enemy.position,
                enemy_top_left,
                enemy_bottom_right,
                Vector2l.new(pixel_scale, pixel_scale)
            )
        end
    end
end

--- Called every frame. Check whether continuous keys are pressed here.
function check_keyboard()
    if Engine.is_key_pressed("A") and player.position.x > 0 then
        player:move(-1 * math.tointeger(math.floor(player.speed * delta_time + 0.5)))
    end

    if Engine.is_key_pressed("D") and player.position.x < player.max_x then
        player:move(math.tointeger(math.floor(player.speed * delta_time + 0.5)))
    end
end


--- Called whenever a key in the listen keys is released.
--- @param key string the released key.
function key_pressed(key)
    if key == Keys.ESCAPE then
        Engine.quit()
    end

    if key == Keys.SPACE then
        player:try_shoot()
    end
end
