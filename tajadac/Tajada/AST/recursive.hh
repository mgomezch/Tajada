#include "Tajada/AST/ArrayAccess.hh"
#include "Tajada/AST/Assignment.hh"
#include "Tajada/AST/Associativity.hh"
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Break.hh"
#include "Tajada/AST/BuiltinFunction.hh"
#include "Tajada/AST/Call.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/ExpressionStatement.hh"
#include "Tajada/AST/For.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/FunctionDefinition.hh"
#include "Tajada/AST/Function.hh"
#include "Tajada/AST/FunctionID.hh"
#include "Tajada/AST/If.hh"
#include "Tajada/AST/InfixFunctionID.hh"
#include "Tajada/AST/Literal.hh"
#include "Tajada/AST/Operator.hh"
#include "Tajada/AST/PrefixFunctionID.hh"
#include "Tajada/AST/Program.hh"
#include "Tajada/AST/Return.hh"
#include "Tajada/AST/Sequence.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/TupleAccessByInteger.hh"
#include "Tajada/AST/TupleAccessByName.hh"
#include "Tajada/AST/TypeAlias.hh"
#include "Tajada/AST/TypeCase.hh"
#include "Tajada/AST/TypeSelection.hh"
#include "Tajada/AST/UnionAccessByInteger.hh"
#include "Tajada/AST/UnionAccessByName.hh"
#include "Tajada/AST/VariableDefinition.hh"
#include "Tajada/AST/VariableUse.hh"
#include "Tajada/AST/While.hh"
