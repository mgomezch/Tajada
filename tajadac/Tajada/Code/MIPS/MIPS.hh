#ifndef TAJADA_CODE_MIPS_MIPS_HH
#define TAJADA_CODE_MIPS_MIPS_HH

#include <unordered_map>

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        extern std::unordered_map<int, int> temp_offsets;

                        extern int next_offset;
                }
        }
}


#endif
