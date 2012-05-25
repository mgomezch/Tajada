#ifndef TAJADA_TYPE_STRUCTURE_HH
#define TAJADA_TYPE_STRUCTURE_HH

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Structure : public virtual Tajada::Type::Type {
                        public:
                                std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems;
                                std::unordered_map<std::string, int> names;

                                Structure(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual Tajada::Type::Type * operator [] (int n) const;
                                virtual Tajada::Type::Type * operator [] (std::string const name) const;

                                virtual unsigned int alignment_();
                };
        }
}

#endif
