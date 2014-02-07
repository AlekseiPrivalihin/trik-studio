#pragma once

#include <QtCore/QObject>

#include "engineCommandBlock.h"

namespace interpreterCore {
namespace coreBlocks {
namespace details {

class EnginesForwardBlock : public EngineCommandBlock
{
	Q_OBJECT

public:
	EnginesForwardBlock(interpreterBase::robotModel::RobotModelInterface &robotModel);
	void run() override;
};

}
}
}
