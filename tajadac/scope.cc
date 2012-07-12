#include <numeric>
#include <string>

// Class:
#include "scope.hh"

#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/Type/Type.hh"

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
                        base = p_parent->end;
                } else {
                        base = 0;
                }

                if (p_type != Tajada::Scope::Type::unspecified || parent == nullptr) {
                        type = p_type;
                } else switch (parent->type) {
                        case Tajada::Scope::Type::unspecified:
                        case Tajada::Scope::Type::global:
                                type = Tajada::Scope::Type::unspecified;
                                break;

                        case Tajada::Scope::Type::main:
                        case Tajada::Scope::Type::main_intermediate:
                                type = Tajada::Scope::Type::main_intermediate;
                                break;

                        case Tajada::Scope::Type::function:
                                base = 0;
                        case Tajada::Scope::Type::function_intermediate:
                                type = Tajada::Scope::Type::function_intermediate;
                                break;
                }

                if (p_type == Tajada::Scope::Type::function) base = 0;
                end = base;
        }



        void Scope::define_variable(
                std::string name,
                Tajada::Type::Type * type
        ) {
                auto a = type->alignment();
                if (a) end += (a - end % a) % a;
                variables[name] = std::make_tuple(type, end);
                end += type->size();
        }



        Tajada::Type::Type * Scope::variable_type(
                std::string name
        ) {
                auto it = variables.find(name);
                return (it != variables.end()) ? std::get<0>(it->second) : nullptr;
        }



        unsigned int Scope::variable_offset(
                std::string name
        ) {
                auto it = variables.find(name);
                return (it != variables.end()) ? std::get<1>(it->second) : 0;
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
                        + u8", base: "
                        + std::to_string(base)
                        + u8"] "
                        + (
                                declaration
                                ? declaration->show() + u8" "
                                : u8""
                        )
                        + u8"{\n"

                        + std::accumulate(
                                variables.begin(),
                                variables.end(),
                                std::string(),
                                [depth](std::string acc, decltype(*variables.begin()) x) {
                                        return
                                                acc
                                                + std::string((depth + 1) * 8, ' ')
                                                + x.first
                                                + u8" es "
                                                + std::get<0>(x.second)->show()
                                                + u8". [[offset: "
                                                + std::to_string(std::get<1>(x.second))
                                                + u8"]]\n"
                                        ;
                                }
                        )

                        + std::accumulate(
                                children.begin(),
                                children.end(),
                                std::string(),
                                [depth](std::string acc, decltype(*children.begin()) x) {
                                        return
                                                acc
                                                + x->show(depth + 1)
                                        ;
                                }
                        )

                        + std::string(depth * 8, ' ')
                        + u8"}\n"
                ;
        }
}
