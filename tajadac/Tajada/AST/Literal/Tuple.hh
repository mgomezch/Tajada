#ifndef TAJADA_AST_LITERAL_TUPLE_HH
#define TAJADA_AST_LITERAL_TUPLE_HH

#include <string>
#include <tuple>
#include <vector>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Tuple : public virtual Tajada::AST::Expression {
                                public:
                                        std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems;

                                        Tuple(
                                                std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * p_elems
                                        );

                                        virtual std::string show(unsigned int depth = 0);

                                        virtual Tajada::Code::Intermediate::Address::Address * genl(
                                                Tajada::Code::Block * b
                                        );

                                        virtual Tajada::Code::Intermediate::Address::Address * genr(
                                                Tajada::Code::Block * b
                                        );
                        };
                }
        }
}

#endif
