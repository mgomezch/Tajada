#include <cassert>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

// Class:
#include "Tajada/AST/Literal/Tuple.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Complex.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Tuple::Tuple(
                                std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * p_elems
                        ):
                                Tajada::AST::AST(),
                                Tajada::AST::Expression(
                                        new Tajada::Type::Tuple(
                                                std::accumulate(
                                                        p_elems->begin(),
                                                        p_elems->end(),
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
                                                p_elems->begin(),
                                                p_elems->end(),
                                                true,
                                                [](
                                                        bool acc,
                                                        std::tuple<Tajada::AST::Expression *, std::string *> * x
                                                ) {
                                                        return acc && std::get<0>(*x)->is_lvalue;
                                                }
                                        )
                                ),

                                elems(p_elems)
                        {}



                        std::string Tuple::show(unsigned int depth) {
                                return
                                        std::string(u8"«")
                                        + (
                                                this->elems->size() == 0
                                                ? u8""
                                                : std::accumulate(
                                                        this->elems->begin(),
                                                        --this->elems->end(),
                                                        std::string(),
                                                        [depth](std::string acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                                return
                                                                        acc
                                                                        + std::get<0>(*x)->show(depth)
                                                                        + u8", "
                                                                ;
                                                        }
                                                )
                                        )
                                        + (this->elems->size() == 0 ? u8"" : std::get<0>(*this->elems->back())->show(depth))
                                        + std::string(u8"»")
                                ;
                        }



                        Tajada::Code::Intermediate::Address::Address * Tuple::genl(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                // TODO: What if one of the tuple’s elements is a reference?  The referred object could be used as an lvalue…
                                // Example: a es queso.  «⋘a⋙»→0 ≔ 42.
                                // That seems reasonable.  Check the specification; update it if necessary.
                                //
                                // Likewise, perhaps all of the assignments implied by assigning one tuple to another happen to be reasonable:
                                // Example: a es queso.  b es queso.  «⋘a⋙, ⋘b⋙» ≔ «27, 42».
                                // This may be analogous or related to what can be achieved in C++ with std::tie: int a = 27, b = 42; std::tie(b, a) = std::make_tuple(a, b);
                                // In fact, that’s precisely what std::tie does: it makes a tuple of references (while std::make_tuple makes a tuple of copies)
                                //
                                // Another case that may or may not be interesting to consider has to do with empty tuples:
                                // Example: «» ≔ «».
                                // Should this be valid?  It implies no assignments, at least as far as the low level interpretation of tuples cares.
                                //
                                // Even if this breaks the notion of tuples being regular first‐class values and assignments being directly to lvalues, it could be too useful to exclude.  Not that this is a real language or anything… but it’d be really cool to be able to do swaps in one instruction without any extra variables.
                                assert(false);

                                return nullptr;
                        }



                        Tajada::Code::Intermediate::Address::Address * Tuple::genr(
                                Tajada::Code::Block * b
                        ) {
                                return std::accumulate(
                                        this->elems->begin(),
                                        this->elems->end(),
                                        new Tajada::Code::Intermediate::Address::Complex(),
                                        [b](
                                                Tajada::Code::Intermediate::Address::Complex * r,
                                                decltype(this->elems->front()) elem
                                        ) {
                                                r->elems.push_back(std::get<0>(*elem)->genr(b));
                                                return r;
                                        }
                                );
                        }
                }
        }
}
