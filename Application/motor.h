#ifndef MOTOR_H
#define MOTOR_H

#include<stdint.h>

class Motor
{
private:
    Motor();
public:
    static uint8_t getLimit(const double & speed, const double & speedUpperLimit);
};

#endif // MOTOR_H
