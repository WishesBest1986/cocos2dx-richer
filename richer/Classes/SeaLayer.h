//
//  SeaLayer.h
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#ifndef __richer__SeaLayer__
#define __richer__SeaLayer__

#include "GameBaseLayer.h"

class SeaLayer : public GameBaseLayer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SeaLayer);
};

#endif /* defined(__richer__SeaLayer__) */
