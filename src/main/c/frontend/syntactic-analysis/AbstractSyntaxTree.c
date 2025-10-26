#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

/** Shutdown module's internal state. */
void _shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		logDebugging(_logger, "Destroying module: AbstractSyntaxTree...");
		destroyLogger(_logger);
		_logger = NULL;
	}
}

ModuleDestructor initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntaxTree");
	return _shutdownAbstractSyntaxTreeModule;
}

/* PUBLIC FUNCTIONS */

void destroyConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}

void destroyExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case ADDITION:
			case DIVISION:
			case MULTIPLICATION:
			case SUBTRACTION:
				destroyExpression(expression->leftExpression);
				destroyExpression(expression->rightExpression);
				break;
			case FACTOR:
				destroyFactor(expression->factor);
				break;
		}
		free(expression);
	}
}

void destroyFactor(Factor * factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case CONSTANT:
				destroyConstant(factor->constant);
				break;
			case EXPRESSION:
				destroyExpression(factor->expression);
				break;
		}
		free(factor);
	}
}

void destroyProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		destroyFunctionDeclaration(program->functionDeclaration);
		free(program);
	}
}

void destroyFunctionDeclaration(FunctionDeclaration * functionDeclaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (functionDeclaration != NULL) {
		free(functionDeclaration->id);
		destroyType(functionDeclaration->returnType);
		destroyParameterList(functionDeclaration->parameters);
		destroyDeclarationList(functionDeclaration->declarationList);
		free(functionDeclaration);
	}
}

void destroyType(Type * type) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (type != NULL) {
		free(type);
	}
}

void destroyParameterList(ParameterList * parameterList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameterList != NULL) {
		Parameter * currentParameter = parameterList->head;
		while (currentParameter != NULL) {
			Parameter * nextParameter = currentParameter->next;
			destroyParameter(currentParameter);
			currentParameter = nextParameter;
		}
		free(parameterList);
	}
}

void destroyParameter(Parameter * parameter) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameter != NULL) {
		free(parameter->id);
		destroyType(parameter->type);
		free(parameter);
	}
}

void destroyDeclarationList(DeclarationList * declarationList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (declarationList != NULL) {
		Declaration * currentDeclaration = declarationList->head;
		while (currentDeclaration != NULL) {
			Declaration * nextDeclaration = currentDeclaration->next;
			destroyDeclaration(currentDeclaration);
			currentDeclaration = nextDeclaration;
		}
		free(declarationList);
	}
}

void destroyDeclaration(Declaration * declaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (declaration != NULL) {
		switch (declaration->declarationType) {
			case VAR_DECLARATION:
				free(declaration->id);
				destroyType(declaration->type);
				break;
			case ASSIGNATTION:
				free(declaration->id);
				destroyType(declaration->type);
				destroyExpression(declaration->expression);
				break;
			case RETURN_STATEMENT:
				destroyExpression(declaration->expression);
				break;
		}
		free(declaration);
	}
}