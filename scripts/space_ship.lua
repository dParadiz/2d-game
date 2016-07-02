name = "space_ship"
animationsList = {
    player = {
        textureId = "player",
        name = "player",
        sequence = {
            { 0, 0, 99, 75 }
        }
    },
    enemy = {
        textureId = "enemy",
        name = "enemy",
        sequence = {
            { 0, 0, 99, 75 }
        }
    },
    laserShot = {
        textureId = "laserShot",
        name = "laserShot",
        sequence = {
            { 0, 0, 9, 33 }
        }
    },
}
transparentColor = { 0, 0, 0, 0 };
textures = {
    player = "../resources/png/player.bmp",
    enemy = "../resources/png/enemyShip.bmp",
    laserShot = "../resources/png/laserRed.bmp",
};
sprites = {

    {
        startPos = { 100, 100, 66, 50 },
        startingAnimation = "player",
        animations = {
            animationsList.player
        },
        controllable = true,
        children = {

        }
    },
    {
        startPos = { 200, 200, 66, 50 },
        startingAnimation = "enemy",
        animations = {
            animationsList.enemy
        },
        controllable = false
    },
    {
        startPos = { 160, 120, 6, 22 },
        startingAnimation = "laserShot",
        animations = {
            animationsList.laserShot
        },
        controllable = true,
        hidden = true,
        bullet = true,
    },
    {
        startPos = { 100, 120, 6, 22 },
        startingAnimation = "laserShot",
        animations = {
            animationsList.laserShot
        },
        controllable = true,
        hidden = true,
        bullet = true,
    },
    {
        startPos = { 130, 120, 6, 22 },
        startingAnimation = "laserShot",
        animations = {
            animationsList.laserShot
        },
        controllable = true,
        hidden = true,
        bullet = true,
    },

}