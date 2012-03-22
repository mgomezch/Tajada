#include <numeric>

#include "scope.hh"

namespace Tajada {
        Scope::Scope(
                Tajada::Scope                    * p_parent,
                Tajada::Scope::Type                p_type,
                Tajada::AST::FunctionDeclaration * p_declaration
        ):
                parent(p_parent),
                declaration(p_declaration)
        {
                if (p_type != Tajada::Scope::Type::unspecified || parent == nullptr) type = p_type;
                else switch (parent->type) {
                        case Tajada::Scope::Type::unspecified:
                        case Tajada::Scope::Type::global:
                                type = Tajada::Scope::Type::unspecified;

                        case Tajada::Scope::Type::main:
                        case Tajada::Scope::Type::main_intermediate:
                                type = Tajada::Scope::Type::main_intermediate;

                        case Tajada::Scope::Type::function:
                        case Tajada::Scope::Type::function_intermediate:
                                type = Tajada::Scope::Type::function_intermediate;
                }
        }

        std::string Scope::show(unsigned int depth) {
                return
                        std::string(depth * 8, ' ')
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
