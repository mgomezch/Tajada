#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/TupleAccessByName.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Integer.hh"
#include "Tajada/Code/Intermediate/Address/Variable.hh"
#include "Tajada/Type/Tuple.hh"

namespace Tajada {
        namespace AST {
                TupleAccessByName::TupleAccessByName(
                        Tajada::AST::Expression * p_source,
                        std::string             * p_field
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Expression(
                                dynamic_cast<Tajada::Type::Tuple &>(*p_source->type)[*p_field],
                                p_source->is_lvalue
                        ),

                        source(p_source),
                        field (p_field )
                {}



                std::string TupleAccessByName::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + u8" → "
                                + *field
                        ;
                }



                Tajada::Code::Intermediate::Address::Address * TupleAccessByName::genl(
                        Tajada::Code::Block * b
                ) {
                        auto sa = this->source->genl(b);
                        if (auto lvar = dynamic_cast<Tajada::Code::Intermediate::Address::Variable *>(sa)) {
                                auto tt = dynamic_cast<Tajada::Type::Tuple *>(this->source->type);
                                assert(tt);

                                lvar->offset += tt->offsets[tt->names[*this->field]];
                                return lvar;
                        } else {
                                assert(false); // TODO: For now, this shouldn’t happen.  Once references are implemented, it might.
                        }
                }



                Tajada::Code::Intermediate::Address::Address * TupleAccessByName::genr(
                        Tajada::Code::Block * b
                ) {
                        auto sa = this->source->genr(b);
                        if (auto lvar = dynamic_cast<Tajada::Code::Intermediate::Address::Variable *>(sa)) {
                                auto tt = dynamic_cast<Tajada::Type::Tuple *>(this->source->type);
                                assert(tt);

                                lvar->offset += tt->offsets[tt->names[*this->field]];
                                return lvar;
                        } else {
                                assert(false); // TODO: For now, this shouldn’t happen.  Once references are implemented, it might.
                        }
                }
        }
}
