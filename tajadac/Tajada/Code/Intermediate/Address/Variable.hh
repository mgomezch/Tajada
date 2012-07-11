#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_VARIABLE_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_VARIABLE_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Location.hh"

#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Variable:
                                        public virtual Tajada::Code::Intermediate::Address::Location
                                {
                                        public:
                                                Tajada::Scope * scope;
                                                std::string   * name ;

                                                Variable(
                                                        Tajada::Scope * p_scope     ,
                                                        std::string   * p_name      ,
                                                        unsigned int    p_offset = 0
                                                );

                                                virtual std::string show();

                                                virtual Tajada::Code::MIPS::Address::Address * to_mips();
                                };
                        }
                }
        }
}

#endif
