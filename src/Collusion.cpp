//
// Created by dejan on 9.1.2016.
//

#include "Collusion.h"
#include <map>

void Collusion::processColisions(int t_width, int t_height, std::vector<Sprite *> t_spriteList) {
    int blockWidth = 30;
    int blockHeight = 30;
    int xBlocks = t_width / blockWidth;
    std::map<int, Sprite *> gridMap;


    for (Sprite *sprite: t_spriteList) {
        SDL_Rect *pos = sprite->getPosition();
        int pos1 = pos->x / blockWidth + xBlocks * pos->y / blockHeight;
        auto sp = gridMap.find(pos1);
        if (sp != gridMap.end()) {
            gridMap[pos1] = sprite;
        } else {
            printf("we have collision\n");
        }
        int pos2 = (pos->x + pos->w) / blockWidth + xBlocks * (pos->y + pos->h) / blockHeight;

        if (pos2 != pos1) {
            gridMap[pos2] = sprite;
        }
        //@todo need to handle all corners
    }
}
