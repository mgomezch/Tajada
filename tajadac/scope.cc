#include "scope.hh"

namespace Tajada {
        Scope::Scope(Scope * parent):
                parent(parent)
        {}
}
