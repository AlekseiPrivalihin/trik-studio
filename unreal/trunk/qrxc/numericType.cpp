#include "numericType.h"

#include <QDebug>

bool NumericType::init(QDomElement const &element)
{
	if (NonGraphicType::init(element))
	{
		QString baseTypeName = element.firstChildElement("base_type").text();
		if (baseTypeName == "int")
			mBaseType = IntType;
		else if (baseTypeName == "float")
			mBaseType = FloatType;
		else
		{
			qDebug() << "ERROR: unknown numeric base type" << baseTypeName;
			return false;
		}
		return true;
	}
	else
		return false;
}
