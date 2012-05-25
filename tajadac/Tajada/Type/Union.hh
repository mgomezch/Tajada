#ifndef TAJADA_TYPE_UNION_HH
#define TAJADA_TYPE_UNION_HH

#include <string>
#include <tuple>
#include <vector>

#include "Tajada/Type/Structure.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Union : public virtual Tajada::Type::Structure {
                        public:
                                Union(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual unsigned int size_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
