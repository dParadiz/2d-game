//
// Created by dejan on 9.1.2016.
//

#ifndef INC_2DGAME_COLLUSION_H
#define INC_2DGAME_COLLUSION_H
#include <vector>
#include "Sprite.h"

class Collusion {

    void processColisions(int t_width, int t_height, std::vector<Sprite*> t_spriteList);
};


#endif //INC_2DGAME_COLLUSION_H
