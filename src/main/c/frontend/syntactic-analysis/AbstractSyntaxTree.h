#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../support/logging/Logger.h"
#include "../../support/type/ModuleDestructor.h"
#include <stdlib.h>

/** Initialize module's internal state. */
ModuleDestructor initializeAbstractSyntaxTreeModule();

/**
 * This type definitions allows self-referencing types (e.g., an expression
 * that is made of another expressions, such as talking about you in 3rd
 * person, but without the madness).
 */

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum DeclarationType DeclarationType;
typedef enum GlobalDeclarationType GlobalDeclarationType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct FunctionDeclaration FunctionDeclaration;
typedef struct Type Type;
typedef struct ParameterList ParameterList;
typedef struct Parameter Parameter;
typedef struct DeclarationList DeclarationList;
typedef struct Declaration Declaration;
typedef struct GlobalDeclaration GlobalDeclaration;
typedef struct GlobalDeclarationList GlobalDeclarationList;
typedef struct DefineDeclaration DefineDeclaration;
typedef struct DefineParameter DefineParameter;
typedef struct DefineParameterList DefineParameterList;
typedef struct DefineCall DefineCall;
typedef struct ArgumentList ArgumentList;
typedef struct Argument Argument;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION,
	DEFINE_CALL
};

enum GlobalDeclarationType {
	FUNCTION_DECLARATION,
	DEFINE_DECLARATION
};

enum DeclarationType {
	VAR_DECLARATION,
	ASSIGNATTION,
	RETURN_STATEMENT,
	DEFINE_CALL_DECLARATION
};

enum FactorType {
	CONSTANT,
	EXPRESSION,
	IDENTIFIER,
    INT_TYPE
};

struct GlobalDeclarationList{
	GlobalDeclaration* head;
};

struct GlobalDeclaration{
	union {
		FunctionDeclaration * functionDeclaration;
		DefineDeclaration * defineDeclaration;
	};
	GlobalDeclarationType type;
	GlobalDeclaration* next;
};

struct DefineDeclaration{
	char* id;
	DefineParameterList* parameterList;
	DeclarationList* declarationList;
};

struct DefineParameterList{
	DefineParameter* head;
};

struct DefineParameter{
	char* id;
	DefineParameter* next;
};



struct FunctionDeclaration{
	char* id;
	Type* returnType;
	ParameterList* parameterList;
	DeclarationList* declarationList;
};

struct Type {
	int type;
};

struct ParameterList{
	Parameter* head;
};

struct Parameter{
	char* id;
	Type* type;
	Parameter* next;
};

struct ArgumentList{
	Argument* head;
};

struct Argument{
	Expression* expression;
	Argument* next;
};


struct DeclarationList{
	Declaration* head;
};


// Si se quiere añadir mas tipos de declaraciones, agregar a la union el nuevo struct e incluir el nuevo tipo en el enum DeclarationType, ademas de el action, destructor y la regla en el bison.
struct Declaration{
	union {
		struct { // type ID; | int x;
			Type* type;
			char* id;
		};/*

		struct{ // type ID = expression; | int x = 10;
			Type* type;
			char* id;
			Expression* expression;
		};*/

		struct { // RETURN expression; | return x + 1;
			Expression* expression;
		};
		
		DefineCall* definecall;
	};
	DeclarationType  declarationType;
	Declaration* next;
};

struct DefineCall{
	char* id;
	ArgumentList* argumentList;
};


struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
		char* id;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
		DefineCall* definecall;
	};
	ExpressionType type;
};

struct Program {
	GlobalDeclarationList * globalDeclarationList;
	Expression* expression;
};

/**
 * Node recursive super-duper-trambolik-destructors.
 */

void destroyConstant(Constant * constant);
void destroyExpression(Expression * expression);
void destroyFactor(Factor * factor);
void destroyProgram(Program * program);
void destroyFunctionDeclaration(FunctionDeclaration * functionDeclaration);
void destroyType(Type * type);
void destroyParameterList(ParameterList * parameterList);
void destroyParameter(Parameter * parameter);
void destroyDeclarationList(DeclarationList * declarationList);
void destroyDeclaration(Declaration * declaration);
void destroyGlobalDeclarationList(GlobalDeclarationList * globalDeclarationList);
void destroyGlobalDeclaration(GlobalDeclaration * globalDeclaration);
void destroyDefineDeclaration(DefineDeclaration * defineDeclaration);
void destroyDefineParameterList(DefineParameterList * defineParameterList);
void destroyDefineParameter(DefineParameter * defineParameter);
void destroyDefineCall(DefineCall* definecall);
void destroyArgumentList(ArgumentList* argumentList);
void destroyArgument(Argument* argument);

#endif
