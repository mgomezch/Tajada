#ifndef TAJADA_AST_LITERAL_TUPLE_HH
#define TAJADA_AST_LITERAL_TUPLE_HH

#include <string>
#include <tuple>
#include <vector>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Tuple : public virtual Tajada::AST::Expression {
                                public:
                                        std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems;

                                        Tuple(std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems);

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
