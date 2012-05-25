#ifndef TAJADA_AST_OPERATOR_HH
#define TAJADA_AST_OPERATOR_HH

namespace Tajada {
        namespace AST {
                enum class Operator : unsigned int {
                        minus      ,
                        plus       ,
                        mult       ,
                        div        ,
                        mod        ,
                        eq         ,
                        neq        ,
                        lessthan   ,
                        greaterthan
                };
        }
}

#endif
