#include "motor.h"
#include <QDebug>

Motor::Motor() {}

uint8_t Motor::getLimit(const double &nominalVoltage, const double & minimumVoltage, const double & speed, const double & upperSpeedLimit)
{
    double V = minimumVoltage*(speed/upperSpeedLimit*2)*(speed/upperSpeedLimit*2);

    double mPart = V/nominalVoltage;

    qDebug() << V;

    double limitd = speed/upperSpeedLimit*(1-mPart);

    limitd += mPart;

    qDebug() << limitd*255;

    return limitd*255;
}
