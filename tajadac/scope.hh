#ifndef TAJADA_SCOPE_HH
#define TAJADA_SCOPE_HH

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "ast.hh"
#include "location.hh"
#include "type.hh"

namespace Tajada {
        class Scope {
                public:
                        enum class Type : unsigned int {
                                unspecified,
                                global,
                                main,
                                function,
                                main_intermediate,
                                function_intermediate
                        };

                        Tajada::Scope * parent;
                        std::unordered_set<Tajada::Scope *> children;
                        std::unordered_map<std::string, Tajada::Type::Type *> variables;
                        std::unordered_map<std::string, Tajada::Type::Type *> aliases;

                        std::unordered_multimap<
                                std::string,
                                std::tuple<
                                        Tajada::Type::Type *,
                                        Tajada::Type::Type *,
                                        Tajada::AST::Function **,
                                        Tajada::yy::location
                                >
                        > functions;

                        Scope::Type type;

                        Tajada::AST::FunctionDeclaration * declaration;

                        Scope(
                                Tajada::Scope                    * p_parent      = nullptr,
                                Tajada::Scope::Type                p_type        = Tajada::Scope::Type::unspecified,
                                Tajada::AST::FunctionDeclaration * p_declaration = nullptr
                        );

                        std::string show(unsigned int depth = 0);
        };
}

#endif
