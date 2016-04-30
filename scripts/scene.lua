scene = {
    name = "menu",
    background = "../resources/spaceShip/farback.bmp",
    resources = "../resource/spaceShip/main_sprite.bmp",
    animations = {
        fly = {
            { 0, 0, 64, 29 },
            { 0, 29, 64, 29 },
            { 0, 58, 64, 29 },
            { 0, 87, 64, 29 },
        },
        idle = {
            { 0, 0, 64, 29 },
        }
    },
    sprites = {
        rocket = {
            name = "rocket",
            startPos = { 100, 100, 64, 29 },
            firstFrame = { 0, 0, 64, 29 }, -- this is not needed probably

        }
    },
    actors = {
        rocekt = {
            sprite = "rocket"
        }
    }

}

return scene;