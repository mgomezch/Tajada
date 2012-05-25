#ifndef TAJADA_AST_fwd_HH
#define TAJADA_AST_fwd_HH

#include "Tajada/AST/Literal/fwd.hh"
#include "Tajada/AST/TypeCase/fwd.hh"

namespace Tajada {
        namespace AST {
                class AST                 ;

                class Statement           ;
                class Block               ;
                class TypeAlias           ;
                class VariableDefinition  ;
                class FunctionID          ;
                class PrefixFunctionID    ;
                class InfixFunctionID     ;
                class FunctionDeclaration ;
                class Function            ;
                class BuiltinFunction     ;
                class FunctionDefinition  ;
                class Program             ;
                class Call                ;
                class VariableUse         ;
                class TupleAccessByInteger;
                class TupleAccessByName   ;
                class UnionAccessByInteger;
                class UnionAccessByName   ;
                class ArrayAccess         ;
                class Sequence            ;
                class ExpressionStatement ;
                class Assignment          ;
                class If                  ;
                class While               ;
                class For                 ;
                class TypeSelection       ;
                class Return              ;
                class Break               ;
        }
}

#endif
