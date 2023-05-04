this.register_on_click(function(x, y)
    local a = dvd.add(math.random(0, sdl.width), math.random(0, sdl.height), "DVD_Blue.png")
    dvd.change_logo_by_id(a.id)
end)

this.register_on_right_click(function(x, y)
    local a = dvd.add(x, y, "DVD_Blue.png")
    dvd.change_logo_by_id(a.id)
end)

this.register_on_middle_click(function(x, y)
    if dvd.count() > 0 then
        dvd.pop()
    end
end)

dvd.register_on_click(function(button, id, d)
    if(button == 0) then
        dvd.set_moving_by_id(id, not d.can_move)
        return 1;
    end
end)
