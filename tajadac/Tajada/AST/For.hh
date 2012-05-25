#ifndef TAJADA_AST_FOR_HH
#define TAJADA_AST_FOR_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class For : public virtual Tajada::AST::Statement {
                        public:
                                std::string * counter;
                                Tajada::AST::Expression * inicio;
                                Tajada::AST::Expression * fin;
                                Tajada::AST::Statement * body;

                                For(
                                        std::string * p_counter,
                                        Tajada::AST::Expression * p_inicio,
                                        Tajada::AST::Expression * p_fin,
                                        Tajada::AST::Statement * p_body
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
