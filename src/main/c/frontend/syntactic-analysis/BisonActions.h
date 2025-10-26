#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../support/logging/Logger.h"
#include "../../support/type/CompilerState.h"
#include "../../support/type/ModuleDestructor.h"
#include "../../support/type/TokenLabel.h"
#include "AbstractSyntaxTree.h"
#include "BisonParser.h"
#include <stdlib.h>

/** Initialize module's internal state. */
ModuleDestructor initializeBisonActionsModule();

/**
 * Bison semantic actions.
 */

Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * functionProgramSemanticAction(FunctionDeclaration * functionDeclaration);
FunctionDeclaration* FunctionDeclarationSemanticAction(Type* type, char* id, ParameterList* parameters, DeclarationList* declarationList);
ParameterList* ParameterListSemanticAction(ParameterList* parameterList, Parameter* parameter);
ParameterList* SingleParameterSemanticAction(Parameter* parameter);
Parameter* ParameterSemanticAction(Type* type, char* id);
DeclarationList* DeclarationListSemanticAction(DeclarationList* declarationList, Declaration* declaration);
DeclarationList* SingleDeclarationSemanticAction(Declaration* declaration);
Declaration* VariableDeclarationSemanticAction(Type* type, char* id);
Declaration* AssignationDeclarationSemanticAction(Type* type, char* id, Expression* expression);
Declaration* ReturnDeclarationSemanticAction(Expression* expression);
Type * IntTypeSemanticAction(TokenLabel token);

Program *DeclarationProgramSemanticAction();
void *SimpleDeclarationSemanticAction();

#endif
