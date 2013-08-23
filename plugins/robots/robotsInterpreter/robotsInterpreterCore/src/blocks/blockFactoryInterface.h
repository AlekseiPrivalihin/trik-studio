#pragma once

#include <robotsInterpreterCore/blocks/blockInterface.h>
#include <robotsInterpreterCore/blocks/blockParserInterface.h>
#include <qrkernel/ids.h>

namespace robotsInterpreterCore {
namespace blocks {

class BlocksFactoryInterface
{
public:
	virtual ~BlocksFactoryInterface() {}

	// TODO: Unneeded, we can supply a parser to a block when we execute it.
	virtual void setParser(BlockParserInterface * const parser) = 0;

	virtual BlockInterface *block(qReal::Id const &element) = 0;
	virtual qReal::IdList providedBlocks() const = 0;

};

}
}
