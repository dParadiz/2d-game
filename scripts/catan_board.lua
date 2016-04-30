name = "catan-board";
background = "../resources/spaceShip/farback.bmp";
resources = "../resource/spaceShip/main_sprite.bmp";
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
};

textures = {
    main = "../resources/spaceShip/main_sprite.bmp"
};

sprites = {
    {
        name = "boardTile1",
        startPos = { 200, 200, 64, 29 },
        firstFrame = { 0, 0, 64, 29 }, -- this is not needed probably
    },
    {
        name = "boardTile2",
        startPos = { 100, 100, 64, 29 },
        firstFrame = { 0, 0, 64, 29 }, -- this is not needed probably
    }
};
actors = {
    rocekt = {
        sprite = "rocket"
    }
};

