--- Configures the application.
--- @param context SetupContext
function setup(context)
    context:set_window_size(500, 500)
    context:set_window_title("LuaToyPainter - Basic")

    local vec = Vector2l.new(5, 7)
    vec:print()
end

--- Handles rendering and logic updates.
--- @param delta_time number # The time elapsed since the last frame, in seconds.
function update(painter, delta_time)
end
