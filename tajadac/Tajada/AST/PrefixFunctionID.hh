#ifndef TAJADA_AST_PREFIXFUNCTIONID_HH
#define TAJADA_AST_PREFIXFUNCTIONID_HH

#include <string>

// Superclasses:
#include "Tajada/AST/FunctionID.hh"

namespace Tajada {
        namespace AST {
                class PrefixFunctionID : public virtual FunctionID {
                        public:
                                PrefixFunctionID(
                                        std::string * p_name
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
