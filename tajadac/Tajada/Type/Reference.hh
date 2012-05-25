#ifndef TAJADA_TYPE_REFERENCE_HH
#define TAJADA_TYPE_REFERENCE_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Reference : public virtual Tajada::Type::Type {
                        public:
                                Tajada::Type::Type * target;

                                Reference(
                                        Tajada::Type::Type * p_target
                                );

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
