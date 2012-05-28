#ifndef TAJADA_AST_VARIABLEUSE_HH
#define TAJADA_AST_VARIABLEUSE_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Type/Type.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Location/Location.hh"

#include "scope.hh"

namespace Tajada {
        class Scope;
}

namespace Tajada {
        namespace AST {
                class VariableUse:
                        public virtual Tajada::AST::Expression
                {
                        public:
                                Tajada::Scope * scope;
                                std::string   * name ;

                                VariableUse(
                                        Tajada::Scope      * p_scope,
                                        std::string        * p_name ,
                                        Tajada::Type::Type * p_type
                                );

                                virtual std::string show(unsigned int depth = 0);

                                Tajada::Code::Intermediate::Location::Location * genl(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
