#ifndef TAJADA_SCOPE_HH
#define TAJADA_SCOPE_HH

#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Tajada/AST/Function.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/Type/Type.hh"
#include "Tajada/Type/Union.hh"

#include "location.hh"

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

                        unsigned int id;

                        unsigned int base;
                        unsigned int end;

                        Tajada::Scope * parent;
                        std::unordered_set<Tajada::Scope *> children;

                        std::unordered_map<
                                std::string,
                                std::tuple<
                                        Tajada::Type::Type *,
                                        unsigned int
                                >
                        > variables;

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
                        Tajada::AST::Statement * structure;

                        Tajada::Type::Union * switch_union;
                        std::string * switch_parameter;

                        Scope(
                                Tajada::Scope                    * p_parent      = nullptr,
                                Tajada::Scope::Type                p_type        = Tajada::Scope::Type::unspecified,
                                Tajada::AST::FunctionDeclaration * p_declaration = nullptr
                        );

                        void define_variable(
                                std::string name,
                                Tajada::Type::Type * type
                        );

                        Tajada::Type::Type * variable_type(
                                std::string name
                        );

                        unsigned int variable_offset(
                                std::string name
                        );

                        std::string show(unsigned int depth = 0);
        };
}

#endif
