#include "xml.hpp"

bool writeXmlFile(QString fileName, QString maxValue, QString minValue)
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

    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();

    return 1;

}

bool parseXmlFile(QString fileName, QString *maxValue, QString *minValue)
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

    return 1;

}
