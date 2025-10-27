#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static CompilerState * _compilerState = NULL;
static Logger * _logger = NULL;

/** Shutdown module's internal state. */
void _shutdownBisonActionsModule() {
	if (_logger != NULL) {
		logDebugging(_logger, "Destroying module: BisonActions...");
		destroyLogger(_logger);
		_logger = NULL;
	}
	_compilerState = NULL;
}

ModuleDestructor initializeBisonActionsModule(CompilerState * compilerState) {
	_compilerState = compilerState;
	_logger = createLogger("BisonActions");
	return _shutdownBisonActionsModule;
}

/* IMPORTED FUNCTIONS */

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	if (factor->type == EXPRESSION) {
        Expression *inner = factor->expression;
        factor->expression = NULL;
        free(factor);
        return inner;
    }
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * IdentifierFactorSemanticAction(char * id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->id = id;
	factor->type = IDENTIFIER;
	return factor;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}

GlobalDeclarationList* GlobalDeclarationListSemanticAction(GlobalDeclarationList* globalDeclarationList, GlobalDeclaration* globalDeclaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlobalDeclaration *it = globalDeclarationList->head;
	while (it->next) {
		it = it->next;
	}
	it->next = globalDeclaration;
	return globalDeclarationList;
}

GlobalDeclarationList* SingleGlobalDeclarationSemanticAction(GlobalDeclaration* globalDeclaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlobalDeclarationList* globalDeclarationList = calloc(1, sizeof(GlobalDeclarationList));
	globalDeclarationList->head = globalDeclaration;
	return globalDeclarationList;
}

Program* DeclarationProgramSemanticAction(GlobalDeclarationList* globalDeclarationList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->globalDeclarationList = globalDeclarationList;
	_compilerState->abstractSyntaxtTree = program; 
	return program;
}

GlobalDeclaration * GlobalFunctionDeclarationSemanticAction(FunctionDeclaration * functionDeclaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlobalDeclaration * globalDeclaration = calloc(1, sizeof(GlobalDeclaration));
	globalDeclaration->functionDeclaration = functionDeclaration;
	globalDeclaration->type = FUNCTION_DECLARATION;
	return globalDeclaration;
}

GlobalDeclaration * GlobalDefineDeclarationSemanticAction(DefineDeclaration * defineDeclaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GlobalDeclaration * globalDeclaration = calloc(1, sizeof(GlobalDeclaration));
	globalDeclaration->defineDeclaration = defineDeclaration;
	globalDeclaration->type = DEFINE_DECLARATION;
	return globalDeclaration;
}

DefineDeclaration* DefineDeclarationSemanticAction(char* id, DefineParameterList* parameterList, DeclarationList* declarationList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefineDeclaration* defineDeclaration = calloc(1, sizeof(DefineDeclaration));
	defineDeclaration->id = id;
	defineDeclaration->parameterList = parameterList;
	defineDeclaration->declarationList = declarationList;
	return defineDeclaration;
}
DefineParameterList * DefineParameterListSemanticAction(DefineParameterList* parameterList, DefineParameter* parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefineParameter *it = parameterList->head;
	while (it->next) {
		it = it->next;
	}
	it->next = parameter;
	return parameterList;
}

DefineParameterList* SingleDefineParameterSemanticAction(DefineParameter* parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefineParameterList* parameterList = calloc(1, sizeof(DefineParameterList));
	parameterList->head = parameter;
	return parameterList;
}

DefineParameter* DefineParameterSemanticAction(char* id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefineParameter* parameter = calloc(1, sizeof(DefineParameter));
	parameter->id = id;
	parameter->next = NULL;
	return parameter;
}


FunctionDeclaration* FunctionDeclarationSemanticAction(Type* type, char* id, ParameterList* parameterList, DeclarationList* declarationList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FunctionDeclaration* functionDeclaration = calloc(1, sizeof(FunctionDeclaration));
	functionDeclaration->returnType = type;
	functionDeclaration->id = id;
	functionDeclaration->parameterList = parameterList;
	functionDeclaration->declarationList = declarationList;
	return functionDeclaration;
}

ParameterList* ParameterListSemanticAction(ParameterList* parameterList, Parameter* parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter *it = parameterList->head;
    while (it->next) {
        it = it->next;
    }
    it->next = parameter;
    return parameterList;
}

ParameterList* SingleParameterSemanticAction(Parameter* parameter) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ParameterList* parameterList = calloc(1, sizeof(ParameterList));
	parameterList->head = parameter;
	return parameterList;
}

Parameter* ParameterSemanticAction(Type* type, char* id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameter* parameter = calloc(1, sizeof(Parameter));
	parameter->type = type;
	parameter->id = id;
	parameter->next = NULL;
	return parameter;
}

DeclarationList* DeclarationListSemanticAction(DeclarationList* declarationList, Declaration* declaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Declaration *it = declarationList->head;
	while (it->next) {
		it = it->next;
	}
	it->next = declaration;
	return declarationList;
}

DeclarationList* SingleDeclarationSemanticAction(Declaration* Declaration) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DeclarationList* declarationList = calloc(1, sizeof(DeclarationList));
	declarationList->head = Declaration;
	return declarationList;
}

Declaration* VariableDeclarationSemanticAction(Type* type, char* id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Declaration* declaration = calloc(1, sizeof(Declaration));
	declaration->type = type;
	declaration->id = id;
	declaration->declarationType = VAR_DECLARATION;
	declaration->next = NULL;
	return declaration;
}

Declaration* AssignationDeclarationSemanticAction(Type* type, char* id, Expression* expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Declaration* declaration = calloc(1, sizeof(Declaration));
	declaration->type = type;
	declaration->id = id;
	declaration->expression = expression;
	declaration->declarationType = ASSIGNATTION;
	declaration->next = NULL;
	return declaration;
}

Declaration* ReturnDeclarationSemanticAction(Expression* expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Declaration* declaration = calloc(1, sizeof(Declaration));
	declaration->expression = expression;
	declaration->declarationType = RETURN_STATEMENT;
	declaration->next = NULL;
	return declaration;
}
Declaration* DefineCallDeclarationSemanticAction(DefineCall* definecall) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Declaration* declaration = calloc(1, sizeof(Declaration));
	declaration->definecall = definecall;
	declaration->declarationType = DEFINE_CALL_DECLARATION;
	declaration->next = NULL;
	return declaration;
}

Expression * DefineCallExpressionSemanticAction(DefineCall* definecall) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->definecall = definecall;
	expression->type = DEFINE_CALL;
	return expression;
}

DefineCall* DefineCallSemanticAction(char* id, ArgumentList* argumentList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefineCall* definecall = calloc(1, sizeof(DefineCall));
	definecall->id = id;
	definecall->argumentList =argumentList;
	return definecall;
}

ArgumentList* ArgumentListSemanticAction(ArgumentList* argumentList, Argument* argument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Argument *it = argumentList->head;
	while (it->next) {
		it = it->next;
	}
	it->next = argument;
	return argumentList;
}

ArgumentList* SingleArgumentSemanticAction(Argument* argument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ArgumentList* argumentList = calloc(1, sizeof(ArgumentList));
	argumentList->head = argument;
	return argumentList;
}

Argument* ArgumentSemanticAction(Expression* expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Argument* argument = calloc(1, sizeof(Argument));
	argument->expression = expression;
	argument->next = NULL;
	return argument;
}
/* 
Program *DeclarationProgramSemanticAction() {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    return NULL;  // más adelante devolverá un nodo del AST
} */

void *SimpleDeclarationSemanticAction() {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    return NULL;
}

Type * IntTypeSemanticAction(TokenLabel token) {
    _logSyntacticAnalyzerAction(__FUNCTION__);

    //Type * type = calloc(1, sizeof(Type));
    //type->type = INT_TYPE;   // o el valor correspondiente en tu enum de tipos
    //return type;
    return NULL;
}