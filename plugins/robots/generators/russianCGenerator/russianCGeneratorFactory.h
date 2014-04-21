#pragma once

#include <generatorBase/generatorFactoryBase.h>

namespace russianC {

class RussianCGeneratorFactory : public generatorBase::GeneratorFactoryBase
{
public:
	RussianCGeneratorFactory(qrRepo::RepoApi const &repo
			, qReal::ErrorReporterInterface &errorReporter
			, interpreterBase::robotModel::RobotModelManagerInterface const &robotModelManager);
	virtual ~RussianCGeneratorFactory();

	QString pathToTemplates() const override;

	generatorBase::simple::Binding::ConverterInterface *stringPropertyConverter() const override;
};

}
