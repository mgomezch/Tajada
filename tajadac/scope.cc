#include <iostream>
#include <numeric>

#include "scope.hh"

unsigned int next_id = 0;

namespace Tajada {
        Scope::Scope(
                Tajada::Scope                    * p_parent,
                Tajada::Scope::Type                p_type,
                Tajada::AST::FunctionDeclaration * p_declaration
        ):
                id              (next_id++    ),
                parent          (p_parent     ),
                declaration     (p_declaration),
                switch_union    (nullptr      ),
                switch_parameter(nullptr      )
        {
                if (p_parent) {
                        if (!p_declaration) p_declaration = p_parent->declaration;
                        structure = p_parent->structure;
                }

                if (p_type != Tajada::Scope::Type::unspecified || parent == nullptr) type = p_type;
                else switch (parent->type) {
                        case Tajada::Scope::Type::unspecified:
                        case Tajada::Scope::Type::global:
                                type = Tajada::Scope::Type::unspecified;
                                break;

                        case Tajada::Scope::Type::main:
                        case Tajada::Scope::Type::main_intermediate:
                                type = Tajada::Scope::Type::main_intermediate;
                                break;

                        case Tajada::Scope::Type::function:
                        case Tajada::Scope::Type::function_intermediate:
                                type = Tajada::Scope::Type::function_intermediate;
                                break;
                }
        }

        void Scope::define_variable(
                std::string name,
                Tajada::Type::Type * type
        ) {
                variables[name] = type;
        }

        Tajada::Type::Type * Scope::variable_type(
                std::string name
        ) {
                auto it = variables.find(name);
                std::cout << "lookup for variable " << name << " in scope " << show() << std::endl;
                return (it != variables.end()) ? it->second : nullptr;
        }

        std::string Scope::show(unsigned int depth) {
                return
                        std::string(depth * 8, ' ')
                        + u8"[id: "
                        + std::to_string(id)
                        + u8", parent: "
                        + (
                                parent
                                ? std::to_string(parent->id)
                                : u8"nullptr"
                        )
                        + u8", type: "
                        + [type]() {
                                switch (type) {
                                        case Tajada::Scope::Type::unspecified          : return u8"unspecified"          ;
                                        case Tajada::Scope::Type::global               : return u8"global"               ;
                                        case Tajada::Scope::Type::main                 : return u8"main"                 ;
                                        case Tajada::Scope::Type::function             : return u8"function"             ;
                                        case Tajada::Scope::Type::main_intermediate    : return u8"main_intermediate"    ;
                                        case Tajada::Scope::Type::function_intermediate: return u8"function_intermediate";
                                }
                                return u8"";
                        } ()
                        + u8"] "
                        + (
                                declaration
                                ? declaration->show() + u8" "
                                : u8""
                        )
                        + std::string(u8"{\n")

                        + std::accumulate(
                                variables.begin(),
                                variables.end(),
                                std::string(),
                                [depth](std::string acc, decltype(*variables.begin()) x) {
                                        return
                                                acc
                                                + std::string((depth + 1) * 8, ' ')
                                                + x.first
                                                + std::string(u8" es ")
                                                + x.second->show()
                                                + std::string(u8"\n");
                                }
                        )

                        + std::accumulate(
                                children.begin(),
                                children.end(),
                                std::string(),
                                [depth](std::string acc, decltype(*children.begin()) x) {
                                        return acc + x->show(depth + 1);
                                }
                        )

                        + std::string(depth * 8, ' ') + std::string(u8"}\n");
        }
}
