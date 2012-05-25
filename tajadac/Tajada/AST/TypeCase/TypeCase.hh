#ifndef TAJADA_AST_TYPECASE_TYPECASE_HH
#define TAJADA_AST_TYPECASE_TYPECASE_HH

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                namespace TypeCase {
                        class TypeCase : public virtual Tajada::AST::AST {
                                public:
                                        Tajada::AST::Statement * body;

                                        TypeCase(
                                                Tajada::AST::Statement * p_body
                                        );
                        };
                }
        }
}

#endif
