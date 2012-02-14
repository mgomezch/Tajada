#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <typeinfo>

#include <sysexits.h>

#include "types.hh"

namespace Tajada {
        namespace types {
                Type::~Type() {}

                std::string Boolean  ::show() { return u8"café"   ; }
                std::string Character::show() { return u8"caraota"; }
                std::string Integer  ::show() { return u8"queso"  ; }
                std::string Float    ::show() { return u8"papelón"; }

                std::string Tuple::show() {
                        switch (elems.size()) {
                                case 0:
                                        return u8"arepa viuda";

                                case 1:
                                        return
                                                u8"arepa de "
                                                + [](std::tuple<Type *, std::string> x) {
                                                        return
                                                                std::get<0>(x)->show()
                                                                + (std::get<1>(x) == "" ? "" : " " + std::get<1>(x));
                                                } (elems.front());

                                default:
                                        return
                                                std::accumulate(
                                                        elems.begin(),
                                                        --elems.end(),
                                                        std::string(u8"arepa con "),
                                                        [](std::string acc, std::tuple<Type *, std::string> t) {
                                                                return
                                                                        acc
                                                                        + std::get<0>(t)->show()
                                                                        + " "
                                                                        + (std::get<1>(t) == "" ? "" : " " + std::get<1>(t) + " ");
                                                        }
                                                )
                                                + u8"y "
                                                + [](std::tuple<Type *, std::string> t) {
                                                        return
                                                                std::get<0>(t)->show()
                                                                + " "
                                                                + (std::get<1>(t) == "" ? "" : " " + std::get<1>(t));
                                                } (elems.back());
                        }
                }

                std::string Union::show() {
                        return
                                u8"cachapa";
                                std::accumulate(
                                        elems.begin(),
                                        --elems.end(),
                                        std::string(u8"cachapa con "),
                                        [](std::string acc, std::tuple<Type *, std::string> t) {
                                                return acc
                                                        + std::get<0>(t)->show()
                                                        + " "
                                                        + (std::get<1>(t) == "" ? "" : " " + std::get<1>(t) + " ");
                                        }
                                )
                                + u8"o "
                                + [](std::tuple<Type *, std::string> t) {
                                        return
                                                std::get<0>(t)->show()
                                                + " "
                                                + (std::get<1>(t) == "" ? "" : " " + std::get<1>(t));
                                } (elems.back());
                }

                std::string Array::show() {
                        return u8"arroz con " + contents->show();
                }

                bool operator == (Type const & l, Type const & r) {
                        if (typeid(l) != typeid(r)) {
                                return false;
                        } else if (typeid(l) == typeid(Tuple)) {
                                return dynamic_cast<Tuple const &>(l).elems    == dynamic_cast<Tuple const &>(r).elems;
                        } else if (typeid(l) == typeid(Union)) {
                                return dynamic_cast<Union const &>(l).elems    == dynamic_cast<Union const &>(r).elems;
                        } else if (typeid(l) == typeid(Array)) {
                                return dynamic_cast<Array const &>(l).contents == dynamic_cast<Array const &>(r).contents;
                        } else std::exit(EX_SOFTWARE);
                }

                bool operator != (Type const & l, Type const & r) {
                        return !(l == r);
                }

        }
}
