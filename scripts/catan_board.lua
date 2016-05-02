name = "catan-board";
animationsList = {
    mountainTile = {
        textureId = "main",
        name = "mountainTile",
        sequence = {
            { 0, 0, 142, 164 }
        }
    },
    clayTile = {
        textureId = "main",
        name = "clayTile",
        sequence = {
            { 0, 4 * 164, 142, 164 }
        }
    },
    seaTile = {
        textureId = "main",
        name = "seaTile",
        sequence = {
            { 0, 2 * 164, 142, 164 }
        }
    },
    forestTile = {
        textureId = "main",
        name = "forestTile",
        sequence = {
            { 0, 3 * 164, 142, 164 }
        }
    },
    wheatTile = {
        textureId = "main",
        name = "wheatTile",
        sequence = {
            { 0, 5 * 164, 142, 164 }
        }
    },
    desertTile = {
        textureId = "main",
        name = "desertTile",
        sequence = {
            { 0, 1 * 164, 142, 164 }
        }
    },
    sheepTile = {
        textureId = "main",
        name = "sheepTile",
        sequence = {
            { 0, 6 * 164, 142, 164 }
        }
    }
};
transparentColor = { 255, 0, 255, 0 };
textures = {
    main = "../resources/catan/board.bmp",
};
startX = 100;
startY = 20;
w = 71;
h = 82;
mapTiles = {
    {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "desertTile",
        animations = {
            animationsList.desertTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "forestTile",
        animations = {
            animationsList.forestTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "forestTile",
        animations = {
            animationsList.forestTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "forestTile",
        animations = {
            animationsList.forestTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "forestTile",
        animations = {
            animationsList.forestTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "sheepTile",
        animations = {
            animationsList.sheepTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "sheepTile",
        animations = {
            animationsList.sheepTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "sheepTile",
        animations = {
            animationsList.sheepTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "sheepTile",
        animations = {
            animationsList.sheepTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "wheatTile",
        animations = {
            animationsList.wheatTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "wheatTile",
        animations = {
            animationsList.wheatTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "wheatTile",
        animations = {
            animationsList.wheatTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "wheatTile",
        animations = {
            animationsList.wheatTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "mountainTile",
        animations = {
            animationsList.mountainTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "clayTile",
        animations = {
            animationsList.clayTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "clayTile",
        animations = {
            animationsList.clayTile
        }
    }, {
        startPos = { 0, 0, 0, 0 },
        startingAnimation = "clayTile",
        animations = {
            animationsList.clayTile
        }
    }
}
sprites = {};
for i = 1, 37 do
    sea = false;

    if (i <= 4) then
        sea = true;
        x = startX + i * w;
        y = startY;
    elseif (i > 4 and i <= 9) then
        sea = (i == 5) or (i == 9);

        x = (startX - w / 2) + (i - 4) * w;
        y = startY + 61;
    elseif (i > 9 and i <= 15) then
        sea = (i == 10) or (i == 15);

        x = (startX - w) + (i - 9) * w;
        y = startY + 2 * 61;
    elseif (i > 15 and i <= 22) then
        sea = (i == 16) or (i == 22);

        x = (startX - 3 * w / 2) + (i - 15) * w;
        y = startY + 3 * 61;
    elseif (i > 22) and i <= 28 then
        sea = (i == 23) or (i == 28);

        x = (startX - w) + (i - 22) * w;
        y = startY + 4 * 61;
    elseif (i > 28) and i <= 33 then
        sea = (i == 29) or (i == 33);

        x = (startX - w / 2) + (i - 28) * w;
        y = startY + 5 * 61;
    elseif (i > 33) and i <= 37 then
        sea = true;
        x = (startX) + (i - 33) * w;
        y = startY + 6 * 61;
    end

    if (sea) then
        table.insert(sprites, {
            startPos = { x, y, w, h },
            startingAnimation = "seaTile",
            animations = {
                animationsList.seaTile -- can not be empty
            }
        });
    else
        rand = math.random(table.getn(mapTiles));
        tile = mapTiles[rand];
        tile["startPos"][1] = x;
        tile["startPos"][2] = y;
        tile["startPos"][3] = w;
        tile["startPos"][4] = h;
        table.insert(sprites, tile);
        table.remove(mapTiles, rand);
    end;
end


