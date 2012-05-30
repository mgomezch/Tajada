#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/UnionAccessByInteger.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/AST/Literal/Integer.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Integer.hh"
#include "Tajada/Code/Intermediate/Address/Variable.hh"
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"
#include "Tajada/Type/Union.hh"

namespace Tajada {
        namespace AST {
                UnionAccessByInteger::UnionAccessByInteger(
                        Tajada::AST::Expression       * p_source,
                        Tajada::AST::Literal::Integer * p_field
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Expression(
                                dynamic_cast<Tajada::Type::Union &>(*p_source->type)[p_field->value],
                                p_source->is_lvalue
                        ),

                        source(p_source),
                        field (p_field )
                {}



                std::string UnionAccessByInteger::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" ⇒ ")
                                + field->show(depth)
                        ;
                }



                Tajada::Code::Intermediate::Address::Address * UnionAccessByInteger::genl(
                        Tajada::Code::Block * b
                ) {
                        auto sa = this->source->genl(b);
                        auto fa = this->field ->genr(b);
                        if (auto lvar = dynamic_cast<Tajada::Code::Intermediate::Address::Variable *>(sa)) {
                                auto ut = dynamic_cast<Tajada::Type::Union *>(this->source->type);
                                assert(ut);

                                auto ii = dynamic_cast<Tajada::Code::Intermediate::Address::Immediate::Integer *>(fa);
                                assert(ii);

                                b->end->instructions.push_back(
                                        new Tajada::Code::Intermediate::Instruction::Copy(
                                                new Tajada::Code::Intermediate::Address::Variable(*lvar),
                                                fa
                                        )
                                );

                                lvar->offset += 32;
                                return lvar;
                        } else {
                                assert(false); // TODO: For now, this shouldn’t happen.  Once references are implemented, it might.
                        }
                }



                Tajada::Code::Intermediate::Address::Address * UnionAccessByInteger::genr(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        assert(false);

                        return nullptr;
                }
        }
}
