#include <numeric>
#include <string>
#include <tuple>
#include <vector>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Tuple.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Tuple::Tuple(
                                std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems
                        ):
                                Tajada::AST::Expression(
                                        new Tajada::Type::Tuple(
                                                std::accumulate(
                                                        elems->begin(),
                                                        elems->end(),
                                                        new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>(),
                                                        [](
                                                                std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * acc,
                                                                std::tuple<Tajada::AST::Expression *, std::string *> * x
                                                        ) {
                                                                acc->push_back(
                                                                        new std::tuple<Tajada::Type::Type *, std::string *>(
                                                                                std::get<0>(*x)->type,
                                                                                std::get<1>(*x)
                                                                        )
                                                                );
                                                                return acc;
                                                        }
                                                )
                                        ),
                                        std::accumulate(
                                                elems->begin(),
                                                elems->end(),
                                                true,
                                                [](
                                                        bool acc,
                                                        std::tuple<Tajada::AST::Expression *, std::string *> * x
                                                ) {
                                                        return acc && std::get<0>(*x)->is_lvalue;
                                                }
                                        )
                                ),
                                elems(elems)
                        {}

                        std::string Tuple::show(unsigned int depth) {
                                return
                                        std::string(u8"«")
                                        + (elems->size() == 0 ? "" :
                                                std::accumulate(
                                                        elems->begin(),
                                                        --elems->end(),
                                                        std::string(),
                                                        [depth](std::string acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                                return
                                                                        acc
                                                                        + std::get<0>(*x)->show(depth)
                                                                        + ", ";
                                                        }
                                                )
                                        )
                                        + (elems->size() == 0 ? "" : std::get<0>(*elems->back())->show(depth))
                                        + std::string(u8"»")
                                ;
                        }
                }
        }
}
