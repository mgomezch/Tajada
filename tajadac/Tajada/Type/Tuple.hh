#ifndef TAJADA_TYPE_TUPLE_HH
#define TAJADA_TYPE_TUPLE_HH

#include <string>
#include <tuple>
#include <vector>

#include "Tajada/Type/Structure.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Tuple : public virtual Tajada::Type::Structure {
                        public:
                                std::unordered_map<int, unsigned int> offsets;

                                Tuple(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual unsigned int size_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
