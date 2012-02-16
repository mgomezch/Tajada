#include <numeric>

#include "scope.hh"

namespace Tajada {
        Scope::Scope(Scope * parent):
                parent(parent)
        {}

        std::string Scope::show(unsigned int depth) {
                return
                        std::string(depth * 8, ' ') + std::string(u8"{\n")

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
