#ifndef TAJADA_BUILTINS_HH
#define TAJADA_BUILTINS_HH

#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>

#include "Tajada/AST/Call.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Builtins {
                typedef
                        std::function<
                                Tajada::Code::Intermediate::Address::Address * (
                                        Tajada::AST::Call   * c,
                                        Tajada::Code::Block * b
                                )
                        >
                        generator
                ;

                typedef
                        std::tuple<
                                Tajada::Type::Type                        *,
                                Tajada::Type::Type                        *,
                                Tajada::Builtins::generator                ,
                                std::function<bool (Tajada::AST::Call *)>
                        >
                        descriptor
                ;

                extern std::unordered_multimap<
                        std::string,
                        Builtins::descriptor
                > builtins;
        }
}

#endif
