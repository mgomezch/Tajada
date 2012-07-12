#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_INSTRUCTION_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_INSTRUCTION_HH

#include <vector>

// Superclasses:
#include "Tajada/Code/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Immediate/Immediate.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/li.hh"
#include "Tajada/Code/MIPS/Instruction/lw.hh"

#define TAJADA_LOAD_TO_REGISTER_MIPS(a, reg, type)                                       \
        dynamic_cast<Tajada::Code::MIPS::Address::Immediate::type *>(a)                  \
        ? static_cast<Tajada::Code::MIPS::Instruction::Instruction *>(                   \
                new Tajada::Code::MIPS::Instruction::li(                                 \
                        dynamic_cast<Tajada::Code::MIPS::Address::Immediate::type *>(a), \
                        new Tajada::Code::MIPS::Address::Register(                       \
                                Tajada::Code::MIPS::Address::Register::R::reg            \
                        )                                                                \
                )                                                                        \
        )                                                                                \
        : static_cast<Tajada::Code::MIPS::Instruction::Instruction *>(                   \
                new Tajada::Code::MIPS::Instruction::lw(                                 \
                        dynamic_cast<Tajada::Code::MIPS::Address::Register *>(a),        \
                        new Tajada::Code::MIPS::Address::Register(                       \
                                Tajada::Code::MIPS::Address::Register::R::reg            \
                        )                                                                \
                )                                                                        \
        )                                                                                \

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Instruction : public virtual Tajada::Code::Instruction {
                                        public:
                                                Instruction();

                                                // TODO: make this pure virtual once all instructions implement translation to MIPS
                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
