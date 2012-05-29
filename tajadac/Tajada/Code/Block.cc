#include <algorithm>
#include <list>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

// Class:
#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace Code {
                Block::Block(
                        std::string p_label
                ):
                        label(p_label),
                        end  (this   )
                {}



                std::string Block::show() {
                        return
                                u8"[" + this->label + u8"] {\n"
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
                                                                return acc + u8", " + b->label;
                                                        }
                                                )
                                                + this->successors.back()->label
                                        )
                                )
                                + u8"]\n"
                        ;
                }



                std::string Block::show_all() {
                        std::unordered_set<Tajada::Code::Block *> bs;
                        std::list<Tajada::Code::Block *> nbs { this };

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
        }
}
