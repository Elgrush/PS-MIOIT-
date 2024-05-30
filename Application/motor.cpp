#include "motor.h"
#include <QDebug>

Motor::Motor() {}

uint8_t Motor::getLimit(const double & speed, const double & speedUpperLimit)
{
    qDebug() << (uint8_t)(speed/speedUpperLimit*255);

    return speed/speedUpperLimit*255;
}
