#ifndef XML_HPP
#define XML_HPP

#include <QFile>
#include <QDebug>
#include<QDir>
#include <QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

bool writeXmlFile(QString fileName, QString maxValue, QString minValue, QString wHeight, QString wWidth, QString x, QString y, QString Period, QString lang);

bool parseXmlFile(QString fileName, QString *maxValue, QString *minValue, QString *wHeight, QString *wWidth, QString *x, QString *y,  QString *Period, QString *lang);

#endif // XML_HPP
