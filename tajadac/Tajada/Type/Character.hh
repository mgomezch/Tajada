#ifndef TAJADA_TYPE_CHARACTER_HH
#define TAJADA_TYPE_CHARACTER_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Character : public virtual Tajada::Type::Type {
                        public:
                                Character();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
