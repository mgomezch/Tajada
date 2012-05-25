#include <algorithm>
#include <numeric>
#include <string>
#include <tuple>

#include "Tajada/Type/Structure.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Union.hh"

#include "Tajada/Type/Type.hh"

#ifndef TAJADA_UNUSED_PARAMETER
#       define TAJADA_UNUSED_PARAMETER(p) static_cast<void>(p);
#endif

namespace Tajada {
        namespace Type {
#define TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL                                     \
        Type(                                                                           \
                std::accumulate(                                                        \
                        p_elems->begin(),                                               \
                        p_elems->end(),                                                 \
                        Tajada::Type::Type::Complete::complete,                         \
                        [](                                                             \
                                Tajada::Type::Type::Complete acc,                       \
                                decltype(*p_elems->begin()) elem                        \
                        ) {                                                             \
                                return                                                  \
                                        acc == Tajada::Type::Type::Complete::incomplete \
                                        ? acc                                           \
                                        : std::get<0>(*elem)->is_complete;              \
                        }                                                               \
                )                                                                       \
        )
                Structure::Structure(
                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * p_elems
                ):
                        TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL,
                        elems(p_elems)
                {
                        auto n = p_elems->size();

                        /* Boring traditional/readable/maintainable/unobfuscated/optimizable programming is boring. */
                        for (unsigned int i = 0; i < n; ++i) {
                                auto nameptr = std::get<1>(*(*p_elems)[i]);
                                if (nameptr) names[*nameptr] = i;
                        }
                }

                Tuple::Tuple(
                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * p_elems
                ):
                        TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL,
                        Tajada::Type::Structure(p_elems)
                {}

                Union::Union(
                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * p_elems
                ):
                        TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL,
                        Tajada::Type::Structure(p_elems)
                {}
#undef TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL

                Tajada::Type::Type * Structure::operator [] (int n) const {
                        if (static_cast<unsigned long>(n) >= elems->size()) return nullptr;

                        return std::get<0>(*(*elems)[n]);
                }

                Tajada::Type::Type * Structure::operator [] (std::string const name) const {
                        auto r = names.find(name);

                        return
                                r == names.end()
                                ? nullptr
                                : (*this)[r->second]
                        ;
                }

                namespace {
                        unsigned int gcd(unsigned int n, unsigned int m) {
                                return
                                        m == 0
                                        ? n
                                        : gcd(m, n % m)
                                ;
                        }

                        unsigned int lcm(unsigned int n, unsigned int m) {
                                return n * m / gcd(n, m);
                        }
                }

                unsigned int Structure::alignment_() {
                        return lcm(32, size());
                }

                unsigned int Tuple::size_() {
                        unsigned int r = 0;

                        for (auto it = elems->begin(); it != elems->end(); ++it) {
                                r += std::get<0>(**it)->size();
                                if (it + 1 != elems->end()) {
                                        auto a = std::get<0>(**(it + 1))->alignment();
                                        if (a) r += (a - r % a) % a;
                                }
                        }

                        return r;
                }

                unsigned int Union::size_() {
                        return
                                std::get<0>(
                                        **std::max_element(
                                                elems->begin(),
                                                elems->end(),
                                                [](
                                                        std::tuple<Tajada::Type::Type *, std::string *> * i,
                                                        std::tuple<Tajada::Type::Type *, std::string *> * j
                                                ) {
                                                        return std::get<0>(*i)->size() < std::get<0>(*j)->size();
                                                }
                                        )
                                )->size();
                }

                std::string Tuple::show(unsigned int depth) {
                        switch (elems->size()) {
                                case 0:
                                        return u8"arepa viuda";

                                case 1:
                                        return
                                                u8"arepa de "
                                                + [depth](std::tuple<Tajada::Type::Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp))
                                                        ;
                                                } (elems->front())
                                        ;

                                default:
                                        return
                                                std::string(u8"arepa con ")
                                                + std::accumulate(
                                                        elems->begin(),
                                                        --(--elems->end()),
                                                        std::string(),
                                                        [depth](std::string acc, std::tuple<Tajada::Type::Type *, std::string *> * tp) {
                                                                return
                                                                        acc
                                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                                        + std::get<0>(*tp)->show(depth)
                                                                        + (*std::get<1>(*tp) == "" ? ", " : " " + *std::get<1>(*tp) + "), ")
                                                                ;
                                                        }
                                                )
                                                + [depth](std::tuple<Tajada::Type::Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp))
                                                        ;
                                                } (*(--(--elems->end())))
                                                + u8" y "
                                                + [depth](std::tuple<Tajada::Type::Type *, std::string *> * tp) {
                                                        return
                                                                (*std::get<1>(*tp) == "" ? "" : "(")
                                                                + std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp) + ")")
                                                        ;
                                                } (*(--elems->end()))
                                        ;
                        }
                }

                std::string Union::show(unsigned int depth) {
                        return
                                u8"cachapa con "
                                + std::accumulate(
                                        elems->begin(),
                                        --(--elems->end()),
                                        std::string(),
                                        [depth](std::string acc, std::tuple<Tajada::Type::Type *, std::string *> * tp) {
                                                return
                                                        acc
                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                        + std::get<0>(*tp)->show(depth)
                                                        + (*std::get<1>(*tp) == "" ? ", " : " " + *std::get<1>(*tp) + "), ")
                                                ;
                                        }
                                )
                                + [depth](std::tuple<Tajada::Type::Type *, std::string *> t) {
                                        return
                                                std::string(*std::get<1>(t) == "" ? "" : "(")
                                                + std::get<0>(t)->show(depth)
                                                + (*std::get<1>(t) == "" ? "" : " " + *std::get<1>(t) + ")")
                                        ;
                                } (**(--(--elems->end())))
                                + u8" o "
                                + [depth](std::tuple<Tajada::Type::Type *, std::string *> t) {
                                        return
                                                std::string(*std::get<1>(t) == "" ? "" : "(")
                                                + std::get<0>(t)->show(depth)
                                                + (*std::get<1>(t) == "" ? "" : " " + *std::get<1>(t) + ")")
                                        ;
                                } (**(--elems->end()))
                        ;
                }
        }
}
