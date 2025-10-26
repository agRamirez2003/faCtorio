%top{

#include "../../support/type/CompilationStatus.h"
#include "../../support/type/FlexContext.h"
#include "../../support/type/TokenLabel.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"

}

%{

/**
 * @see https://westes.github.io/flex/manual/Definitions-Section.html#Definitions-Section
 */

extern CompilationStatus ArithmeticOperatorLexemeAction(TokenLabel label);
extern CompilationStatus EnterMultilineCommentLexemeAction(FlexContext context);
extern CompilationStatus EOFLexemeAction();
extern CompilationStatus IgnoredLexemeAction();
extern CompilationStatus IntegerLexemeAction();
extern CompilationStatus LeaveMultilineCommentLexemeAction();
extern CompilationStatus ParenthesisLexemeAction(TokenLabel label);
extern CompilationStatus SubexpressionLexemeAction();
extern CompilationStatus UnknownLexemeAction();
extern CompilationStatus KeywordLexemeAction();
extern CompilationStatus IdentifierLexemeAction();
extern CompilationStatus SemicolonLexemeAction();
extern CompilationStatus CommaLexemeAction();
extern CompilationStatus DefineLexemeAction();
extern CompilationStatus EnterDeclarationBlockLexemeAction(FlexContext context);
extern CompilationStatus LeaveDeclarationBlockLexemeAction();

%}

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x DECLARATION_BLOCK
%x MULTILINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */
whitespace			[[:space:]]+

%%

%{

/**
 * @see https://westes.github.io/flex/manual/Rules-Section.html#Rules-Section
 */

%}

"{"									                    { return EnterDeclarationBlockLexemeAction(DECLARATION_BLOCK); }
<DECLARATION_BLOCK>"int"                                { return KeywordLexemeAction(INT); }
<DECLARATION_BLOCK>[a-zA-Z_][a-zA-Z0-9_]*               { return IdentifierLexemeAction(); }
<DECLARATION_BLOCK>"}"				                    { return LeaveDeclarationBlockLexemeAction(); }
<DECLARATION_BLOCK>"-"									{ return ArithmeticOperatorLexemeAction(SUB); }
<DECLARATION_BLOCK>"*"									{ return ArithmeticOperatorLexemeAction(MUL); }
<DECLARATION_BLOCK>"/"									{ return ArithmeticOperatorLexemeAction(DIV); }
<DECLARATION_BLOCK>"+"									{ return ArithmeticOperatorLexemeAction(ADD); }
<DECLARATION_BLOCK>";"                                  { return SemicolonLexemeAction(); }
<DECLARATION_BLOCK>{whitespace}						    { return IgnoredLexemeAction(); }
<DECLARATION_BLOCK>.				                    { return UnknownLexemeAction(); }

"/*"								{ return EnterMultilineCommentLexemeAction(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"*/"				{ return LeaveMultilineCommentLexemeAction(); }
<MULTILINE_COMMENT>[^*]+			{ return IgnoredLexemeAction(); }
<MULTILINE_COMMENT>.				{ return IgnoredLexemeAction(); }



"("									{ return ParenthesisLexemeAction(OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(CLOSE_PARENTHESIS); }

","                                 { return CommaLexemeAction(); }

[[:digit:]]+						{ return IntegerLexemeAction(); }


"int"                               { return KeywordLexemeAction(INT); }
"bool"                              { return KeywordLexemeAction(BOOL); }
"point"                             { return KeywordLexemeAction(POINT); }
"#DEFINE"                           { return DefineLexemeAction(); }
[a-zA-Z_][a-zA-Z0-9_]*              { return IdentifierLexemeAction(); }



{whitespace}						{ return IgnoredLexemeAction(); }
.									{ return UnknownLexemeAction(); }

<<EOF>>								{ return EOFLexemeAction(); }

%%

/**
 * @see https://westes.github.io/flex/manual/User-Code-Section.html#User-Code-Section
 */

#include "FlexActions.h"
#include "FlexExport.h"
