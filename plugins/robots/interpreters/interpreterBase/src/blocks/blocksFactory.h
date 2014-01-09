#pragma once

#include <qrkernel/ids.h>

#include <interpreterBase/blocks/block.h>
#include <interpreterBase/blocks/blockParserInterface.h>
#include <interpreterBase/blocks/blocksTableInterface.h>
#include <interpreterBase/blocks/blocksFactoryInterface.h>
#include <interpreterBase/robotModel/robotModelInterface.h>

namespace interpreterBase {
namespace blocks {

class BlocksFactory : public BlocksFactoryInterface
{
public:
	BlocksFactory(qReal::GraphicalModelAssistInterface const &graphicalModelApi
			, qReal::LogicalModelAssistInterface const &logicalModelApi
			, robotModel::RobotModelInterface * const robotModel
			, qReal::ErrorReporterInterface * const errorReporter
			);

	virtual BlockInterface *block(qReal::Id const &element);

	virtual void setParser(BlockParserInterface * const parser);

//	RobotsBlockParser * getParser();

	virtual qReal::IdList providedBlocks() const;

private:
	static bool elementMetatypeIs(qReal::Id const &element, QString const &metatype);
	static qReal::Id id(QString const &metatype);

	robotModel::RobotModelInterface * mRobotModel;  // Doesnt't have ownership
	qReal::GraphicalModelAssistInterface const &mGraphicalModelApi;
	qReal::LogicalModelAssistInterface const &mLogicalModelApi;
	qReal::ErrorReporterInterface * const mErrorReporter;  // Doesn't have ownership
	BlockParserInterface * mParser;
};

}
}
