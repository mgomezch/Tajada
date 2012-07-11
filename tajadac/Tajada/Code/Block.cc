#include <algorithm>
#include <list>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

// Class:
#include "Tajada/Code/Block.hh"

#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/MIPS.hh"

namespace Tajada {
        class Scope;

        unsigned int getScopeEnd(Tajada::Scope * scope);
}

namespace Tajada {
        namespace Code {
                unsigned long int Block::next_label = 0;



                Block::Block(
                        std::string     p_label,
                        Tajada::Scope * p_scope,
                        unsigned int    p_index
                ):
                        label(p_label),
                        scope(p_scope),
                        index(p_index),
                        end  (this   )
                {}



                std::string Block::getLabel() {
                        return
                                this->label
                                + "_"
                                + std::to_string(this->index)
                        ;
                }

                std::string Block::rawLabel() {
                        return this->label;
                }

                std::string Block::show() {
                        return
                                u8"[" + this->getLabel() + u8"] {\n"
                                + std::accumulate(
                                        this->instructions.begin(),
                                        this->instructions.end(),
                                        std::string(),
                                        [](std::string acc, Tajada::Code::Instruction * i) {
                                                return
                                                        acc
                                                        + u8"        "
                                                        + i->show()
                                                        + u8";\n"
                                                ;
                                        }
                                )
                                + u8"} → ["
                                + (
                                        this->successors.empty()
                                        ? u8""
                                        : (
                                                std::accumulate(
                                                        this->successors.begin(),
                                                        --this->successors.end(),
                                                        std::string(),
                                                        [](std::string acc, Tajada::Code::Block * b) {
                                                                return acc + b->getLabel() + u8", ";
                                                        }
                                                )
                                                + this->successors.back()->getLabel()
                                        )
                                )
                                + u8"]\n"
                        ;
                }



                std::unordered_set<Tajada::Code::Block *> reachable_from(Tajada::Code::Block * init) {
                        std::unordered_set<Tajada::Code::Block *> bs;
                        std::list<Tajada::Code::Block *> nbs { init };

                        std::for_each(
                                nbs.begin(),
                                nbs.end(),
                                [&bs, &nbs](Tajada::Code::Block * b) {
                                        if (bs.count(b)) return;
                                        bs.insert(b);
                                        nbs.insert(
                                                nbs.end(),
                                                b->successors.begin(),
                                                b->successors.end()
                                        );
                                }
                        );

                        return bs;
                }



                std::string Block::show_all() {
                        auto bs = reachable_from(this);

                        return
                                std::accumulate(
                                        bs.begin(),
                                        bs.end(),
                                        std::string(),
                                        [](std::string acc, Tajada::Code::Block * b) {
                                                return acc + b->show() + "\n";
                                        }
                                )
                        ;
                }



                Block * Block::to_mips() {
                        Tajada::Code::MIPS::temp_offsets.clear();
                        Tajada::Code::MIPS::next_offset = Tajada::getScopeEnd(this->scope);
                        return std::accumulate(
                                this->instructions.begin(),
                                this->instructions.end(),
                                new Tajada::Code::Block(this->getLabel() + "_mips", nullptr),
                                [](
                                        Tajada::Code::Block       * acc,
                                        Tajada::Code::Instruction * i
                                ) {
                                        if (auto ii = dynamic_cast<Tajada::Code::Intermediate::Instruction::Instruction *>(i)) {
                                                auto mi = ii->to_mips();
                                                acc->instructions.insert(acc->instructions.end(), mi.begin(), mi.end());
                                        }
                                        return acc;
                                }
                        );
                }



                std::string Block::to_mips_all() {
                        auto bs = reachable_from(this);

                        return
                                std::accumulate(
                                        bs.begin(),
                                        bs.end(),
                                        std::string(),
                                        [](std::string acc, Tajada::Code::Block * b) {
                                                return acc + b->to_mips()->show() + "\n";
                                        }
                                )
                        ;
                }



                unsigned long int Block::make_label() {
                        return next_label++;
                }
        }
}
