#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <typeinfo>

#include <sysexits.h>

#include "type.hh"

namespace Tajada {
        namespace Type {
                Type::~Type() {}

                std::string Boolean  ::show() { return u8"café"   ; }
                std::string Character::show() { return u8"caraota"; }
                std::string Integer  ::show() { return u8"queso"  ; }
                std::string Float    ::show() { return u8"papelón"; }

                Tuple::Tuple(std::list<std::tuple<Tajada::Type::Type *, std::string *> *> * elems):
                        elems(elems)
                {}

                Tajada::Type::Type * Tuple::operator [] (int n) const {
                        if (static_cast<unsigned long>(n) >= elems->size()) return NULL;

                        // Coño.  Coño.  Coño.  ¿Por qué coño no usé std::vector para todo desde el principio?  Coño, ¿std::list?  A qué clase de imbécil se le ocurre hacer un std::list para esto en C++11, con move constructors y rvalue references?  A mí.  Ahora hay que cambiar todo, coño.  Piratería temporal:
                        for (auto it = elems->begin(); it != elems->end() && n >= 0; ++it, --n) {
                                if (n == 0) return std::get<0>(**it);
                        }
                        return NULL;
                }

                Tajada::Type::Type * Tuple::operator [] (std::string const name) const {
                        for (auto it = elems->begin(); it != elems->end(); ++it) {
                                if (name == *std::get<1>(**it)) return std::get<0>(**it);
                        }
                        return NULL;
                }

                std::string Tuple::show() {
                        switch (elems->size()) {
                                case 0:
                                        return u8"arepa viuda";

                                case 1:
                                        return
                                                u8"arepa de "
                                                + [](std::tuple<Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show()
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp));
                                                } (elems->front());

                                default:
                                        return
                                                std::accumulate(
                                                        elems->begin(),
                                                        --elems->end(),
                                                        std::string(u8"arepa con "),
                                                        [](std::string acc, std::tuple<Type *, std::string *> * tp) {
                                                                return
                                                                        acc
                                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                                        + std::get<0>(*tp)->show()
                                                                        + " "
                                                                        + (*std::get<1>(*tp) == "" ? "" : *std::get<1>(*tp) + ") ");
                                                        }
                                                )
                                                + u8"y "
                                                + [](std::tuple<Type *, std::string *> * tp) {
                                                        return
                                                                std::get<0>(*tp)->show()
                                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp));
                                                } (elems->back());
                        }
                }

                std::string Union::show() {
                        return
                                u8"cachapa";
                                std::accumulate(
                                        elems->begin(),
                                        --elems->end(),
                                        std::string(u8"cachapa con "),
                                        [](std::string acc, std::tuple<Type *, std::string *> * tp) {
                                                return acc
                                                        + (*std::get<1>(*tp) == "" ? "" : "(")
                                                        + std::get<0>(*tp)->show()
                                                        + " "
                                                        + (*std::get<1>(*tp) == "" ? "" : *std::get<1>(*tp) + ") ");
                                        }
                                )
                                + u8"o "
                                + [](std::tuple<Type *, std::string *> * tp) {
                                        return
                                                std::string(*std::get<1>(*tp) == "" ? "" : "(")
                                                + std::get<0>(*tp)->show()
                                                + (*std::get<1>(*tp) == "" ? "" : " " + *std::get<1>(*tp) + ")");
                                } (elems->back());
                }

                Array::Array(Type * contents):
                        contents(contents)
                {}

                std::string Array::show() {
                        return u8"arroz con " + contents->show();
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
