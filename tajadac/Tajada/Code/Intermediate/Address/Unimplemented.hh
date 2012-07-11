#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_UNIMPLEMENTED_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_UNIMPLEMENTED_HH

// TODO: remove this file once all subclasses have their implementation of genl/genr

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

//#include "Tajada/AST/AST.hh"
namespace Tajada {
        namespace AST {
                class AST;
        }
}

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Unimplemented:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                Tajada::AST::AST * unimplemented;

                                                Unimplemented(
                                                        Tajada::AST::AST * p_unimplemented
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
