#include "motor.h"
#include <QDebug>

Motor::Motor() {}

uint8_t Motor::getLimit(const double & speed, const double & speedUpperLimit, const int & period)
{
    qDebug() << (uint8_t)(speed/speedUpperLimit*period);

    return speed/speedUpperLimit*period;
}
