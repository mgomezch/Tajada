#ifndef TAJADA_TYPE_ARRAY_HH
#define TAJADA_TYPE_ARRAY_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Array : public virtual Tajada::Type::Type {
                        public:
                                Tajada::Type::Type * contents;
                                unsigned int length;

                                Array(
                                        Tajada::Type::Type * p_contents
                                );

                                Array(
                                        Tajada::Type::Type * p_contents,
                                        unsigned int p_length
                                );

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
