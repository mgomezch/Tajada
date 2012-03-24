#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <typeinfo>

#include "type.hh"

#ifndef TAJADA_UNUSED_PARAMETER
#       define TAJADA_UNUSED_PARAMETER(p) static_cast<void>(p);
#endif

namespace Tajada {
        namespace Type {
                Type::Type(
                        Type::Complete p_is_complete
                ):
                        is_complete        (p_is_complete),
                        has_saved_size     (false        ),
                        has_saved_alignment(false        )
                {}

                unsigned int Type::size() {
                        if (has_saved_size) return saved_size;
                        has_saved_size = true;
                        return size_();
                }

                unsigned int Type::alignment() {
                        if (has_saved_alignment) return saved_alignment;
                        has_saved_alignment = true;
                        return alignment_();
                }

                Type::~Type() {}

#define TAJADA_BASIC_TYPE(n, str, s, a)                                                                      \
                std::string n::show(unsigned int depth) { TAJADA_UNUSED_PARAMETER(depth); return u8"" str; } \
                unsigned int n::size_     () { return s; }                                                   \
                unsigned int n::alignment_() { return a; }                                                   \
                n::n(): Type(Tajada::Type::Type::Complete::complete) {}
                TAJADA_BASIC_TYPE(Boolean  , "café"   ,  1,  8)
                TAJADA_BASIC_TYPE(Character, "caraota", 32, 32)
                TAJADA_BASIC_TYPE(Integer  , "queso"  , 32, 32)
                TAJADA_BASIC_TYPE(Float    , "papelón", 32, 32)
#undef TAJADA_BASIC_TYPE

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

                        /* Boring traditional/readable/maintainable/unobfuscated programming is boring. */
                        for (unsigned int i = 0; i < n; ++i) {
                                auto nameptr = std::get<1>(*(*p_elems)[i]);
                                if (nameptr) names[*nameptr] = i;
                        }
                }

                Tuple::Tuple(
                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * p_elems
                ):
                        TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL,
                        Structure(p_elems)
                {}

                Union::Union(
                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * p_elems
                ):
                        TAJADA_TYPE_STRUCTURE_TYPE_CONSTRUCTOR_CALL,
                        Structure(p_elems)
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
                                : (*this)[r->second];
                }

                namespace {
                        unsigned int gcd(unsigned int n, unsigned int m) {
                                return
                                        m == 0
                                        ? n
                                        : gcd(m, n % m);
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
                                        r += a - r % a;
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
                                                + [depth](std::tuple<Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp));
                                                } (elems->front());

                                default:
                                        return
                                                std::string(u8"arepa con ")
                                                + std::accumulate(
                                                        elems->begin(),
                                                        --(--elems->end()),
                                                        std::string(),
                                                        [depth](std::string acc, std::tuple<Type *, std::string *> * tp) {
                                                                return
                                                                        acc
                                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                                        + std::get<0>(*tp)->show(depth)
                                                                        + (*std::get<1>(*tp) == "" ? ", " : " " + *std::get<1>(*tp) + "), ");
                                                        }
                                                )
                                                + [depth](std::tuple<Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp));
                                                } (*(--(--elems->end())))
                                                + u8" y "
                                                + [depth](std::tuple<Type *, std::string *> * tp) {
                                                        return
                                                                (*std::get<1>(*tp) == "" ? "" : "(")
                                                                + std::get<0>(*tp)->show(depth)
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp) + ")");
                                                } (*(--elems->end()));
                        }
                }

                std::string Union::show(unsigned int depth) {
                        return
                                u8"cachapa con "
                                + std::accumulate(
                                        elems->begin(),
                                        --(--elems->end()),
                                        std::string(),
                                        [depth](std::string acc, std::tuple<Type *, std::string *> * tp) {
                                                return
                                                        acc
                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                        + std::get<0>(*tp)->show(depth)
                                                        + (*std::get<1>(*tp) == "" ? ", " : " " + *std::get<1>(*tp) + "), ");
                                        }
                                )
                                + [depth](std::tuple<Type *, std::string *> t) {
                                        return
                                                std::string(*std::get<1>(t) == "" ? "" : "(")
                                                + std::get<0>(t)->show(depth)
                                                + (*std::get<1>(t) == "" ? "" : " " + *std::get<1>(t) + ")");
                                } (*(--(--elems->back())))
                                + u8" o "
                                + [depth](std::tuple<Type *, std::string *> t) {
                                        return
                                                std::string(*std::get<1>(t) == "" ? "" : "(")
                                                + std::get<0>(t)->show(depth)
                                                + (*std::get<1>(t) == "" ? "" : " " + *std::get<1>(t) + ")");
                                } (*(--elems->back()));
                }

                Array::Array(
                        Type * p_contents
                ):
                        Type(Tajada::Type::Type::Complete::incomplete),
                        contents(p_contents),
                        length(0)
                {}

                Array::Array(
                        Type * p_contents,
                        unsigned int p_length
                ):
                        Type(p_contents->is_complete),
                        contents(p_contents),
                        length(p_length)
                {}

                unsigned int Array::size_() {
                        auto s = contents->size();
                        auto a = contents->alignment();
                        return length * (s + a - s % a);
                }

                unsigned int Array::alignment_() {
                        return contents->alignment();
                }

                std::string Array::show(unsigned int depth) {
                        return
                                u8"arroz con "
                                + contents->show(depth);
                }

                Reference::Reference(
                        Type * p_target
                ):
                        Type(Tajada::Type::Type::Complete::complete),
                        target(p_target)
                {}

                unsigned int Reference::size_     () { return 32; }
                unsigned int Reference::alignment_() { return 32; }

                std::string Reference::show(unsigned int depth) {
                        return
                                u8"⋘"
                                + target->show(depth)
                                + u8"⋙";
                }

                bool operator == (Type const & l, Type const & r) {
                        if (typeid(l) != typeid(r)) {
                                return false;
                        } else if (typeid(l) == typeid(Tuple)) {
                                auto el = dynamic_cast<Tuple const &>(l).elems;
                                auto er = dynamic_cast<Tuple const &>(r).elems;
                                if (el->size() != er->size()) return false;
                                for (auto itl = el->begin(), itr = er->begin(); itl != el->end() && itr != er->end(); ++itl, ++itr) {
                                        if (*std::get<1>(**itl) != *std::get<1>(**itr)) return false;
                                        if (*std::get<0>(**itl) != *std::get<0>(**itr)) return false;
                                }
                                return true;
                        } else if (typeid(l) == typeid(Union)) {
                                auto el = dynamic_cast<Tuple const &>(l).elems;
                                auto er = dynamic_cast<Tuple const &>(r).elems;
                                if (el->size() != er->size()) return false;
                                for (auto itl = el->begin(), itr = er->begin(); itl != el->end() && itr != er->end(); ++itl, ++itr) {
                                        if (*std::get<1>(**itl) != *std::get<1>(**itr)) return false;
                                        if (*std::get<0>(**itl) != *std::get<0>(**itr)) return false;
                                }
                                return true;
                        } else if (typeid(l) == typeid(Array)) {
                                return *dynamic_cast<Array const &>(l).contents == *dynamic_cast<Array const &>(r).contents;
                        } else if (typeid(l) == typeid(Reference)) {
                                return *dynamic_cast<Reference const &>(l).target == *dynamic_cast<Reference const &>(r).target;
                        } else {
                                return true;
                        }
                }

                bool operator != (Type const & l, Type const & r) {
                        return !(l == r);
                }

        }
}
