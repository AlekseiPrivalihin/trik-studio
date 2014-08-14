HEADERS += \
	$$PWD/tokenPatterns.h \
	$$PWD/parserError.h \
	$$PWD/textLanguageParser.h \
	$$PWD/textLanguageParserInterface.h \
	$$PWD/tokenType.h \
	$$PWD/semanticAnalyzer.h \
	$$PWD/ast/connection.h \
	$$PWD/ast/range.h \
	$$PWD/ast/nodes/node.h \
	$$PWD/ast/nodes/unaryOperator.h \
	$$PWD/ast/nodes/binaryOperator.h \
	$$PWD/ast/nodes/number.h \
	$$PWD/ast/nodes/unaryMinus.h \
	$$PWD/ast/nodes/not.h \
	$$PWD/ast/nodes/bitwiseNegation.h \
	$$PWD/ast/nodes/length.h \
	$$PWD/ast/nodes/addition.h \
	$$PWD/ast/nodes/subtraction.h \
	$$PWD/ast/nodes/multiplication.h \
	$$PWD/ast/nodes/division.h \
	$$PWD/ast/nodes/integerDivision.h \
	$$PWD/ast/nodes/modulo.h \
	$$PWD/ast/nodes/exponentiation.h \
	$$PWD/ast/nodes/bitwiseAnd.h \
	$$PWD/ast/nodes/bitwiseOr.h \
	$$PWD/ast/nodes/bitwiseXor.h \
	$$PWD/ast/nodes/bitwiseLeftShift.h \
	$$PWD/ast/nodes/bitwiseRightShift.h \
	$$PWD/ast/nodes/concatenation.h \
	$$PWD/ast/nodes/equality.h \
	$$PWD/ast/nodes/lessThan.h \
	$$PWD/ast/nodes/lessOrEqual.h \
	$$PWD/ast/nodes/inequality.h \
	$$PWD/ast/nodes/greaterThan.h \
	$$PWD/ast/nodes/greaterOrEqual.h \
	$$PWD/ast/nodes/integerNumber.h \
	$$PWD/ast/nodes/floatNumber.h \
	$$PWD/ast/nodes/fieldInitialization.h \
	$$PWD/ast/nodes/expression.h \
	$$PWD/ast/nodes/tableConstructor.h \
	$$PWD/ast/nodes/integerNumber.h \
	$$PWD/ast/nodes/floatNumber.h \
	$$PWD/ast/nodes/string.h \
	$$PWD/ast/nodes/true.h \
	$$PWD/ast/nodes/false.h \
	$$PWD/ast/nodes/nil.h \
	$$PWD/ast/nodes/identifier.h \
	$$PWD/ast/nodes/functionCall.h \
	$$PWD/ast/nodes/methodCall.h \
	$$PWD/ast/nodes/assignment.h \
	$$PWD/ast/nodes/block.h \
	$$PWD/ast/nodes/indexingExpression.h \
	$$PWD/types/typeExpression.h \
	$$PWD/types/typeVariable.h \
	$$PWD/types/nil.h \
	$$PWD/types/any.h \
	$$PWD/types/boolean.h \
	$$PWD/types/integer.h \
	$$PWD/types/float.h \
	$$PWD/types/string.h \
	$$PWD/types/number.h \
	$$PWD/types/function.h \
	$$PWD/types/table.h \
	$$PWD/types/generalizationsTable.h \
	$$PWD/details/lexer.h \
	$$PWD/details/token.h  \
	$$PWD/details/tokenStream.h  \
	$$PWD/details/parserRef.h \
	$$PWD/details/parserContext.h \
	$$PWD/details/precedenceTable.h \
	$$PWD/details/temporaryNodes/temporaryToken.h \
	$$PWD/details/temporaryNodes/temporaryPair.h \
	$$PWD/details/temporaryNodes/temporaryList.h \
	$$PWD/details/temporaryNodes/temporaryDiscardableNode.h \
	$$PWD/details/parsers/parserCombinators.h \
	$$PWD/details/parsers/tokenParser.h \
	$$PWD/details/parsers/simpleParser.h \
	$$PWD/details/parsers/parserInterface.h \
	$$PWD/details/parsers/alternativeParser.h \
	$$PWD/details/parsers/transformingParser.h \
	$$PWD/details/parsers/concatenationParser.h \
	$$PWD/details/parsers/optionalParser.h \
	$$PWD/details/parsers/kleeneStarParser.h \
	$$PWD/details/parsers/expressionParser.h \
	$$PWD/details/utils/functionTraits.h \

SOURCES += \
	$$PWD/tokenPatterns.cpp \
	$$PWD/parserError.cpp \
	$$PWD/textLanguageParser.cpp \
	$$PWD/semanticAnalyzer.cpp \
	$$PWD/ast/connection.cpp \
	$$PWD/ast/range.cpp \
	$$PWD/ast/nodes/node.cpp \
	$$PWD/details/lexer.cpp \
	$$PWD/details/token.cpp \
	$$PWD/details/tokenStream.cpp \
	$$PWD/details/precedenceTable.cpp \
	$$PWD/types/typeVariable.cpp \
	$$PWD/types/generalizationsTable.cpp \
