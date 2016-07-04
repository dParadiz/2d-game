name = "space_ship"
animationsList = {
    player = {
        textureId = "player",
        name = "player",
        fps = 5,
        sequence = {
            { 0, 0, 99, 75 },
			{ 0, 75, 99, 75 },
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
        startPos = { 100, 500, 66, 50 },
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
        controllable = false,
        enemyAI = true,

    },
    {
        startPos = { 700, 10, 66, 50 },
        startingAnimation = "enemy",
        animations = {
            animationsList.enemy
        },
        controllable = false,
        enemyAI = true,

    },
 {
        startPos = { 100, 0, 66, 50 },
        startingAnimation = "enemy",
        animations = {
            animationsList.enemy
        },
        controllable = false,
        enemyAI = true,

    },

    {
        startPos = { 100, 50, 66, 50 },
        startingAnimation = "enemy",
        animations = {
            animationsList.enemy
        },
        controllable = false,
        enemyAI = true,

    },
    {
        startPos = { 160, 520, 6, 22 },
        startingAnimation = "laserShot",
        animations = {
            animationsList.laserShot
        },
        controllable = true,
        hidden = true,
        ammunition = true,
    },
    {
        startPos = { 100, 520, 6, 22 },
        startingAnimation = "laserShot",
        animations = {
            animationsList.laserShot
        },
        controllable = true,
        hidden = true,
        ammunition = true,
    },

}
