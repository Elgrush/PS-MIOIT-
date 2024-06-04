#include "xml.hpp"

bool writeXmlFile(QString fileName, QString maxValue, QString minValue, QString wHeight, QString wWidth, QString x, QString y, QString Period, QString lang)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return 0;

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(1);

    stream.writeStartDocument();

    stream.writeStartElement("Limits");

    stream.writeStartElement("Minimum");
    stream.writeAttribute("Value", minValue);
    stream.writeEndElement();

    stream.writeStartElement("Maximum");
    stream.writeAttribute("Value", maxValue);
    stream.writeEndElement();


    stream.writeStartElement("Period");
    stream.writeAttribute("Value", Period);
    stream.writeEndElement();


    stream.writeStartElement("wHeight");
    stream.writeAttribute("Value", wHeight);
    stream.writeEndElement();

    stream.writeStartElement("wWidth");
    stream.writeAttribute("Value", wWidth);
    stream.writeEndElement();

    stream.writeStartElement("Position");
    stream.writeAttribute("X", x);
    stream.writeAttribute("Y", y);
    stream.writeEndElement();

    stream.writeStartElement("lang");
    stream.writeAttribute("Value", lang);
    stream.writeEndElement();

    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();

    return 1;

}

bool parseXmlFile(QString fileName, QString *maxValue, QString *minValue, QString *wHeight, QString *wWidth, QString *x, QString *y, QString *Period, QString *lang)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return 0;

    QDomDocument doc;

    if(!(doc.setContent(&file)))
        return 0;

    QDomElement root = doc.documentElement();
    QDomElement sibling = root.firstChildElement();

    while(sibling.toElement().tagName() != "Maximum")
    {
        sibling= sibling.nextSiblingElement();
        qDebug() << sibling.toElement().tagName();
    }

    *maxValue = sibling.toElement().attribute("Value");

    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="Minimum")
    {
        sibling= sibling.nextSiblingElement();
    };

    *minValue = sibling.toElement().attribute("Value");


    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="Period")
    {
        sibling= sibling.nextSiblingElement();
    };

    *Period = sibling.toElement().attribute("Value");

    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="wHeight")
    {
        sibling= sibling.nextSiblingElement();
    };

    *wHeight = sibling.toElement().attribute("Value");


    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="wWidth")
    {
        sibling= sibling.nextSiblingElement();
    };

    *wWidth = sibling.toElement().attribute("Value");

    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="Position")
    {
        sibling= sibling.nextSiblingElement();
    };

    *x = sibling.toElement().attribute("X");

    *y = sibling.toElement().attribute("Y");

    sibling = root.firstChildElement();
    while(sibling.toElement().tagName()!="lang")
    {
        sibling= sibling.nextSiblingElement();
    };

    *lang = sibling.toElement().attribute("Value");

    return 1;

}
