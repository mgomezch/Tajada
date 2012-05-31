#ifndef TAJADA_AST_FUNCTIONID_HH
#define TAJADA_AST_FUNCTIONID_HH

#include <string>

// Superclasses:
#include "Tajada/AST/AST.hh"

namespace Tajada {
        namespace AST {
                class FunctionID:
                        public virtual Tajada::AST::AST
                {
                        public:
                                std::string * name;

                                FunctionID(
                                        std::string * p_name
                                );

                                virtual std::string show(unsigned int depth = 0) = 0;
                };
        }
}

#endif
