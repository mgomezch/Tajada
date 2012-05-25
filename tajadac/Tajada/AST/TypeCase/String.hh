#ifndef TAJADA_AST_TYPECASE_STRING_HH
#define TAJADA_AST_TYPECASE_STRING_HH

// Superclasses:
#include "Tajada/AST/TypeCase/TypeCase.hh"

#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                namespace TypeCase {
                        class String : public virtual Tajada::AST::TypeCase::TypeCase {
                                public:
                                        std::string * index;

                                        String(
                                                std::string * p_index,
                                                Tajada::AST::Statement * p_body
                                        );

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
