//
// Created by Albert on 10/31/18.
//

#ifndef ZOPADRAMMACHINE_SIMPLEDELAY_H
#define ZOPADRAMMACHINE_SIMPLEDELAY_H
#include <memory>
#include "google/RenderableAudio.h"
#include "const.h"
class SimpleDelay: public RenderableAudio {

public:
    SimpleDelay(float timeSec, float decay);

    void renderAudio(int16_t *targetData, int32_t numFrames);

private:
    unsigned int position = 0;
    size_t size;
    int16_t* buffer;
    float decay;
};


#endif //ZOPADRAMMACHINE_SIMPLEDELAY_H
