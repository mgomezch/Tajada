#include <string>
#include <tuple>
#include <typeinfo>

// Class:
#include "Tajada/Type/Type.hh"

#include "Tajada/Type/Array.hh"
#include "Tajada/Type/Reference.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Union.hh"

namespace Tajada {
        namespace Type {
                Type::Type(
                        Tajada::Type::Type::Complete p_is_complete
                ):
                        is_complete        (p_is_complete),
                        has_saved_size     (false        ),
                        has_saved_alignment(false        )
                {}

                unsigned int Type::size() {
                        if (has_saved_size) return saved_size;
                        has_saved_size = true;
                        return saved_size = size_();
                }

                unsigned int Type::alignment() {
                        if (has_saved_alignment) return saved_alignment;
                        has_saved_alignment = true;
                        return saved_alignment = alignment_();
                }

                Type::~Type() {}

                bool operator == (Tajada::Type::Type const & l, Tajada::Type::Type const & r) {
                        if (typeid(l) != typeid(r)) {
                                return false;
                        } else if (typeid(l) == typeid(Tajada::Type::Tuple)) {
                                auto el = dynamic_cast<Tajada::Type::Tuple const &>(l).elems;
                                auto er = dynamic_cast<Tajada::Type::Tuple const &>(r).elems;
                                if (el->size() != er->size()) return false;
                                for (auto itl = el->begin(), itr = er->begin(); itl != el->end() && itr != er->end(); ++itl, ++itr) {
                                        if (*std::get<1>(**itl) != *std::get<1>(**itr)) return false;
                                        if (*std::get<0>(**itl) != *std::get<0>(**itr)) return false;
                                }
                                return true;
                        } else if (typeid(l) == typeid(Tajada::Type::Union)) {
                                auto el = dynamic_cast<Tajada::Type::Tuple const &>(l).elems;
                                auto er = dynamic_cast<Tajada::Type::Tuple const &>(r).elems;
                                if (el->size() != er->size()) return false;
                                for (auto itl = el->begin(), itr = er->begin(); itl != el->end() && itr != er->end(); ++itl, ++itr) {
                                        if (*std::get<1>(**itl) != *std::get<1>(**itr)) return false;
                                        if (*std::get<0>(**itl) != *std::get<0>(**itr)) return false;
                                }
                                return true;
                        } else if (typeid(l) == typeid(Tajada::Type::Array)) {
                                return *dynamic_cast<Tajada::Type::Array const &>(l).contents == *dynamic_cast<Tajada::Type::Array const &>(r).contents;
                        } else if (typeid(l) == typeid(Tajada::Type::Reference)) {
                                return *dynamic_cast<Tajada::Type::Reference const &>(l).target == *dynamic_cast<Tajada::Type::Reference const &>(r).target;
                        } else {
                                return true;
                        }
                }

                bool operator != (Tajada::Type::Type const & l, Tajada::Type::Type const & r) {
                        return !(l == r);
                }
        }
}
