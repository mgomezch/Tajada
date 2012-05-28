#ifndef TAJADA_CODE_INTERMEDIATE_LOCATION_VARIABLE_HH
#define TAJADA_CODE_INTERMEDIATE_LOCATION_VARIABLE_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Location/Location.hh"

#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Location {
                                class Variable:
                                        public virtual Tajada::Code::Intermediate::Location::Location
                                {
                                        Tajada::Scope * scope;
                                        std::string   * name ;

                                        Variable(
                                                Tajada::Scope * p_scope,
                                                std::string   * p_name
                                        );

                                        virtual std::string show();
                                };
                        }
                }
        }
}

#endif
