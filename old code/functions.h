#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "sensors/Ultrasonic.h"


class functions {
private:
    std::vector<int> leftDistances;
    std::vector<int> rightDistances;
    float d = 1.0f;
    static constexpr size_t BUFFER_SIZE = 10;
    static constexpr int THRESHOLD = 45;


    float computeAverageDelta(const std::vector<int>& buffer);
    

public:
    void addToBufferL(int value);
    void addToBufferR(int value);
    float angleCheck();
    void correction();
    void clearBuffers();

};


#endif