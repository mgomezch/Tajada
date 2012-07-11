// Class:
#include "Tajada/Code/MIPS/Instruction/Unimplemented.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

// TODO: remove this whole class once every intermediate instruction gets translated
namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                Unimplemented::Unimplemented(
                                        Tajada::Code::Intermediate::Instruction::Instruction * p_untranslated
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        untranslated(p_untranslated)
                                {}



                                std::string Unimplemented::show() {
                                        return
                                                "# UNIMPLEMENTED ("
                                                + this->untranslated->show()
                                                + ")"
                                        ;
                                }
                        }
                }
        }
}
