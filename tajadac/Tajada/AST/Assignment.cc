#include <cassert>
#include <string>
#include <unordered_map>

// Class:
#include "Tajada/AST/Assignment.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Complex.hh"
#include "Tajada/Code/Intermediate/Address/Temporary.hh"
#include "Tajada/Code/Intermediate/Address/Variable.hh"
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Union.hh"

namespace Tajada {
        namespace AST {
                Assignment::Assignment(
                        Tajada::AST::Expression * lhs,
                        Tajada::AST::Expression * rhs
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        lhs(lhs),
                        rhs(rhs)
                {}



                std::string Assignment::show(unsigned int depth) {
                        return
                                lhs->show(depth)
                                + std::string(u8" ≔ ")
                                + rhs->show(depth)
                        ;
                }



                static void flatten(
                        Tajada::Code::Block * b,
                        Tajada::Code::Intermediate::Address::Variable lv,
                        Tajada::Code::Intermediate::Address::Address * rv,
                        std::unordered_map<
                                Tajada::Code::Intermediate::Address::Variable  *,
                                Tajada::Code::Intermediate::Address::Temporary *
                        > * finals
                ) {
                        if (auto rvs = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(rv)) {
                                auto n = rvs->elems.size();
                                for (unsigned int i = 0; i < n; ++i) {
                                        flatten(
                                                b,
                                                Tajada::Code::Intermediate::Address::Variable(
                                                        lv.scope,
                                                        lv.name,
                                                        lv.offset + rvs->type->offsets[i]
                                                ),
                                                rvs->elems[i],
                                                finals
                                        );
                                }
                        } else {
                                auto v = new Tajada::Code::Intermediate::Address::Variable(lv);
                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                (*finals)[v] = t;
                                b->end->instructions.push_back(
                                        new Tajada::Code::Intermediate::Instruction::Copy(
                                                t,
                                                rv
                                        )
                                );
                        }
                }



                void Assignment::gen(
                        Tajada::Code::Block * b
                ) {
                        auto lv = this->lhs->genl(b);
                        auto rv = this->rhs->genr(b);
                        std::unordered_map<
                                Tajada::Code::Intermediate::Address::Variable  *,
                                Tajada::Code::Intermediate::Address::Temporary *
                        > finals;

                        if (auto lvar = dynamic_cast<Tajada::Code::Intermediate::Address::Variable *>(lv)) {
                                flatten(
                                        b,
                                        *lvar,
                                        rv,
                                        &finals
                                );
                                for (auto it = finals.begin(); it != finals.end(); ++it) {
                                        b->end->instructions.push_back(
                                                new Tajada::Code::Intermediate::Instruction::Copy(
                                                        it->first,
                                                        it->second
                                                )
                                        );
                                }
                        } else {
                                assert(false); // TODO: For now, this shouldn’t happen.  Once references are implemented, it might.
                        }
                }
        }
}
