#include "nullKitInterpreterInterface.h"

using namespace nullKitInterpreter;

QString NullKitInterpreterInterface::kitId() const
{
	return "nullKit";
}

QWidget *NullKitInterpreterInterface::settingsWidget() const
{
	return NULL;
}

//QList<QWidget *> NullKitInterpreterInterface::toolWidgets() const
//{
//	return QList<QWidget *>();
//}

//QList<robotsInterpreterCore::SensorId> NullKitInterpreterInterface::sensorIds() const
//{
//	return QList<robotsInterpreterCore::SensorId>();
//}

qReal::IdList NullKitInterpreterInterface::specificBlocks() const
{
	return qReal::IdList();
}

qReal::IdList NullKitInterpreterInterface::unsupportedBlocks() const
{
	return qReal::IdList();
}
