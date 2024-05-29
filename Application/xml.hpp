#ifndef XML_HPP
#define XML_HPP

#include <QFile>
#include <QDebug>
#include<QDir>
#include <QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

bool writeXmlFile(QString fileName, QString maxValue, QString minValue);

bool parseXmlFile(QString fileName, QString *maxValue, QString *minValue);

#endif // XML_HPP
