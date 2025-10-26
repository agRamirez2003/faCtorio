%{

#include "../../support/type/TokenLabel.h"
#include "AbstractSyntaxTree.h"
#include "BisonActions.h"

/**
 * The error reporting function for Bison parser.
 *
 * @todo Add location to the grammar and "pushToken" API function.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Error-Reporting-Function.html
 * @see https://www.gnu.org/software/bison/manual/html_node/Tracking-Locations.html
 */
void yyerror(const YYLTYPE * location, const char * message) {}

%}

// You touch this, and you die.
%define api.pure full
%define api.push-pull push
%define api.value.union.name SemanticValue
%define parse.error detailed
%locations

%union {
	/** Terminals. */

	signed int integer;
	TokenLabel token;
	char* string;

	/** Non-terminals. */

	FunctionDeclaration * functionDeclaration;
	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	ParameterList * parameterList;
	DeclarationList * declarationList;
	Parameter * parameter;
	Type * type;
	Declaration * declaration;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach for the AST root node ("program" non-terminal, in this
 * grammar), or it will drop the entire tree even if the parsing succeeds.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
%destructor { destroyConstant($$); } <constant>
%destructor { destroyExpression($$); } <expression>
%destructor { destroyFactor($$); } <factor>
%destructor { destroyType($$); } <type>
%destructor { destroyParameter($$); } <parameter>
%destructor { destroyParameterList($$); } <parameterList>
%destructor { destroyDeclaration($$); } <declaration>
%destructor { destroyDeclarationList($$); } <declarationList>
%destructor { destroyFunctionDeclaration($$); } <functionDeclaration>

/** Terminals. */
%token <token> COMMA
%token <integer> INTEGER
%token <token> ADD
%token <token> CLOSE_BRACE
%token <token> CLOSE_COMMENT
%token <token> CLOSE_PARENTHESIS
%token <token> DIV
%token <token> MUL
%token <token> OPEN_BRACE
%token <token> OPEN_COMMENT
%token <token> OPEN_PARENTHESIS
%token <token> SUB
%token <token> INT
%token <token> BOOL
%token <token> POINT
%token <token> DEFINE
%token <string> ID
%token <token> SEMICOLON
%token <token> RETURN
%token <token> EQUALS

%token <token> IGNORED
%token <token> UNKNOWN

/** Non-terminals. */
%type <functionDeclaration> functionDeclaration
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program
%type <declaration> declaration
%type <parameterList> parameterList
%type <declarationList> declarationList
%type <parameter> parameter
%type <type> type

/**
 * Precedence and associativity.
 *
 * @see https://en.cppreference.com/w/cpp/language/operator_precedence.html
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

// IMPORTANT: To use λ in the following grammar, use the %empty symbol.

program: functionDeclaration								{ $$ = functionProgramSemanticAction($1); }
	;

functionDeclaration: type ID OPEN_PARENTHESIS parameterList CLOSE_PARENTHESIS OPEN_BRACE declarationList CLOSE_BRACE { $$ = FunctionDeclarationSemanticAction($1, $2, $4, $7); }
	;	



parameterList: parameterList COMMA parameter				{ $$ = ParameterListSemanticAction($1, $3); }
	| parameter												{ $$ = SingleParameterSemanticAction($1); }
	| 														{ $$ = NULL; }
	;

parameter: type ID											{ $$ = ParameterSemanticAction($1, $2); }
	;

declarationList: declarationList declaration				{ $$ = DeclarationListSemanticAction($1, $2); }
	| declaration 											{ $$ = SingleDeclarationSemanticAction($1); }
	|														{ $$ = NULL; }
	;

declaration: type ID SEMICOLON							{ $$ = VariableDeclarationSemanticAction($1, $2); }
	| type ID EQUALS expression SEMICOLON				{ $$ = AssignationDeclarationSemanticAction($1, $2, $4); }
	| RETURN expression SEMICOLON						{ $$ = ReturnDeclarationSemanticAction($2); }
	;



expression: expression[left] ADD expression[right]			{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor												{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS		{ $$ = ExpressionFactorSemanticAction($2); }
	| constant												{ $$ = ConstantFactorSemanticAction($1); }
	| ID										            { $$ = IdentifierFactorSemanticAction($1); }	
	;

constant: INTEGER											{ $$ = IntegerConstantSemanticAction($1); }
	;

type: INT												{ $$ = IntTypeSemanticAction($1); }
	;

%%
