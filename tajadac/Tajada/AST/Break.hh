#ifndef TAJADA_AST_BREAK_HH
#define TAJADA_AST_BREAK_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                class Break : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Statement * statement;

                                Break(
                                        Tajada::AST::Statement * statement
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
