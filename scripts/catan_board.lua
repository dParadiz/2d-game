name = "catan-board";
animationsList = {
    mountainTile = {
        textureId = "main",
        name = "mountainTile",
        sequence = {
            { 0, 0, 142, 164 }
        }
    },

};
transparentColor = {255, 0, 255, 0}

textures = {
    main = "../resources/catan/board.bmp",

};

sprites = {

    {
        name = "boardTile1", -- currently not needed
        startPos = { 200, 20, 142, 164 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile -- can not be empty
        }
    },
    {
        name = "boardTile1", -- currently not needed
        startPos = { 342, 20, 142, 164 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile -- can not be empty
        }
    },
    {
        name = "boardTile1", -- currently not needed
        startPos = { 271, 102, 142, 164 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile -- can not be empty
        }
    }

};


