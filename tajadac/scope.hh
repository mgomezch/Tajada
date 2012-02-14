#ifndef TAJADA_SCOPE_HH
#define TAJADA_SCOPE_HH

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "types.hh"

namespace Tajada {
        class Scope {
                public:
                        Scope * parent;
                        std::unordered_set<Scope *> children;
                        std::unordered_map<std::string, Tajada::types::Type *> symbols;

                        Scope(Scope * parent = NULL);
        };
}

#endif
