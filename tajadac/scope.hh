#ifndef TAJADA_SCOPE_HH
#define TAJADA_SCOPE_HH

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "ast.hh"
#include "type.hh"

namespace Tajada {
        class Scope {
                public:
                        Scope * parent;
                        std::unordered_set<Scope *> children;
                        std::unordered_map<std::string, Tajada::Type::Type *> variables;
                        std::unordered_map<std::string, Tajada::Type::Type *> aliases;
                        std::unordered_multimap<std::string, std::tuple<Tajada::Type::Type *, Tajada::Type::Type *, Tajada::AST::FunctionDefinition *>> functions;

                        Scope(Scope * parent = NULL);

                        std::string show(unsigned int depth = 0);
        };
}

#endif
