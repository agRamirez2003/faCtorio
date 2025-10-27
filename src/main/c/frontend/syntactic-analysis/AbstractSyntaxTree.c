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
        logDebugging(_logger, "Executing destructor not null: %s", __FUNCTION__);
        //        destroyFactor(expression->factor);
        //logDebugging(_logger, "Executing destructor not nulllllll: %s", FUNCTION);
        //        return ;
        switch (expression->type) {
            case ADDITION:
            case DIVISION:
            case MULTIPLICATION:
            case SUBTRACTION:
                logDebugging(_logger, "Executing destructor arithmetic: %s", __FUNCTION__);
                destroyExpression(expression->leftExpression);
                destroyExpression(expression->rightExpression);
                break;
            case FACTOR:
                logDebugging(_logger, "Executing destructor factor: %s", __FUNCTION__);
                destroyFactor(expression->factor);
                break;
			case DEFINE_CALL:
				logDebugging(_logger, "Executing destructor define call: %s", __FUNCTION__);
				destroyDefineCall(expression->definecall);
				break;
            default:
                logDebugging(_logger, "Unknown ExpressionType in destructor: %s", __FUNCTION__);
                break;
        }
        logDebugging(_logger, "Freeing expression memory: %s", __FUNCTION__);
        free(expression);
    }
    else{
        logDebugging(_logger, "Executing destructor null: %s", __FUNCTION__);
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
			case IDENTIFIER:
				free(factor->id);
				break;	
		}
		free(factor);
	}
}

void destroyProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		destroyGlobalDeclarationList(program->globalDeclarationList);
		free(program);
	}
}

void destroyFunctionDeclaration(FunctionDeclaration * functionDeclaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (functionDeclaration != NULL) {
		free(functionDeclaration->id);
		destroyType(functionDeclaration->returnType);
		destroyParameterList(functionDeclaration->parameterList);
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

void destroyGlobalDeclarationList(GlobalDeclarationList * globalDeclarationList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (globalDeclarationList != NULL) {
		GlobalDeclaration * currentGlobalDeclaration = globalDeclarationList->head;
		while (currentGlobalDeclaration != NULL) {
			GlobalDeclaration * nextGlobalDeclaration = currentGlobalDeclaration->next;
			destroyGlobalDeclaration(currentGlobalDeclaration);
			currentGlobalDeclaration = nextGlobalDeclaration;
		}
		free(globalDeclarationList);
	}
}

void destroyGlobalDeclaration(GlobalDeclaration * globalDeclaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (globalDeclaration != NULL) {
		switch (globalDeclaration->type) {
			case FUNCTION_DECLARATION:
				destroyFunctionDeclaration(globalDeclaration->functionDeclaration);
				break;
			case DEFINE_DECLARATION:
				destroyDefineDeclaration(globalDeclaration->defineDeclaration);
				break;
		}
		free(globalDeclaration);
	}
}

void destroyDefineDeclaration(DefineDeclaration * defineDeclaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (defineDeclaration != NULL) {
		free(defineDeclaration->id);
		destroyDefineParameterList(defineDeclaration->parameterList);
		destroyDeclarationList(defineDeclaration->declarationList);
		free(defineDeclaration);
	}
}

void destroyDefineParameterList(DefineParameterList * defineParameterList) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (defineParameterList != NULL) {
		DefineParameter * currentParameter = defineParameterList->head;
		while (currentParameter != NULL) {
			DefineParameter * nextParameter = currentParameter->next;
			destroyDefineParameter(currentParameter);
			currentParameter = nextParameter;
		}
		free(defineParameterList);
	}
}

void destroyDefineParameter(DefineParameter * defineParameter) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (defineParameter != NULL) {
		free(defineParameter->id);
		free(defineParameter);
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
                //destroyType(declaration->type);
                destroyExpression(declaration->expression);
                break;
            case RETURN_STATEMENT:
                destroyExpression(declaration->expression);
                break;
			case DEFINE_CALL_DECLARATION:
				destroyDefineCall(declaration->definecall);
				break;
        }
        free(declaration);
    }
}

void destroyDefineCall(DefineCall* definecall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(definecall != NULL){
		free(definecall->id);
		destroyArgumentList(definecall->argumentList);
		free(definecall);
	}
}

void destroyArgumentList(ArgumentList* argumentList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(argumentList != NULL){
		Argument* currentArgument = argumentList->head;
		while(currentArgument != NULL){
			Argument* nextArgument = currentArgument->next;
			destroyArgument(currentArgument);
			currentArgument = nextArgument;
		}
		free(argumentList);
	}
}

void destroyArgument(Argument* argument){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(argument != NULL){
		destroyExpression(argument->expression);
		free(argument);
	}
}