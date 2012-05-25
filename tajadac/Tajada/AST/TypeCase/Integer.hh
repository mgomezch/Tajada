#ifndef TAJADA_AST_TYPECASE_INTEGER_HH
#define TAJADA_AST_TYPECASE_INTEGER_HH

// Superclasses:
#include "Tajada/AST/TypeCase/TypeCase.hh"

#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                namespace TypeCase {
                        class Integer : public virtual Tajada::AST::TypeCase::TypeCase {
                                public:
                                        int index;

                                        Integer(
                                                std::string * p_index,
                                                Tajada::AST::Statement * p_body
                                        );

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
