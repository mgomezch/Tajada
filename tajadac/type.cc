#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <typeinfo>

#include <sysexits.h>

#include "type.hh"

#ifndef TAJADA_UNUSED_PARAMETER
#       define TAJADA_UNUSED_PARAMETER(p) static_cast<void>(p);
#endif

namespace Tajada {
        namespace Type {
                Type::Type(Type::Complete p_is_complete): is_complete(p_is_complete) {}
                Type::~Type() {}

                std::string Boolean  ::show(unsigned int depth) { TAJADA_UNUSED_PARAMETER(depth); return u8"café"   ; }
                std::string Character::show(unsigned int depth) { TAJADA_UNUSED_PARAMETER(depth); return u8"caraota"; }
                std::string Integer  ::show(unsigned int depth) { TAJADA_UNUSED_PARAMETER(depth); return u8"queso"  ; }
                std::string Float    ::show(unsigned int depth) { TAJADA_UNUSED_PARAMETER(depth); return u8"papelón"; }

                Boolean  ::Boolean  (): Type(Tajada::Type::Type::Complete::complete) {}
                Character::Character(): Type(Tajada::Type::Type::Complete::complete) {}
                Integer  ::Integer  (): Type(Tajada::Type::Type::Complete::complete) {}
                Float    ::Float    (): Type(Tajada::Type::Type::Complete::complete) {}

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
                        /* Boring maintainable/readable/unobfuscated/traditional programming is boring. ☹ */
                        auto n = p_elems->size();

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

                std::string Array::show(unsigned int depth) {
                        return
                                u8"arroz con "
                                + contents->show(depth);
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
                        } else {
                                return true;
                        }
                }

                bool operator != (Type const & l, Type const & r) {
                        return !(l == r);
                }

        }
}
