#ifndef TAJADA_AST_EXPRESSION_HH
#define TAJADA_AST_EXPRESSION_HH

#include <string>

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                class Expression : public virtual Tajada::AST::AST {
                        public:
                                Tajada::Type::Type * type;
                                bool is_lvalue;

                                Expression(
                                        Tajada::Type::Type * type,
                                        bool is_lvalue
                                );

                                // TODO: make this pure virtual once all subclasses have their implementation
                                virtual Tajada::Code::Intermediate::Address::Address * genl(
                                        Tajada::Code::Block * b
                                );

                                // TODO: make this pure virtual once all subclasses have their implementation
                                virtual Tajada::Code::Intermediate::Address::Address * genr(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
