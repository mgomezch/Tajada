#ifndef TAJADA_TYPES_HH
#define TAJADA_TYPES_HH

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

namespace Tajada {
        namespace Type {
                class Type {
                        public:
                                enum class Complete : bool {
                                        incomplete,
                                        complete
                                } is_complete;

                                Type(Complete p_is_complete);

                                virtual std::string show(unsigned int depth = 0) = 0;

                                virtual ~Type() = 0;
                };

                class Boolean : public virtual Type {
                        public:
                                Boolean();

                                virtual std::string show(unsigned int depth = 0);
                };

                class Character : public virtual Type {
                        public:
                                Character();

                                virtual std::string show(unsigned int depth = 0);
                };

                class Integer : public virtual Type {
                        public:
                                Integer();

                                virtual std::string show(unsigned int depth = 0);
                };

                class Float : public virtual Type {
                        public:
                                Float();

                                virtual std::string show(unsigned int depth = 0);
                };

                class Structure : public virtual Type {
                        public:
                                std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems;
                                std::unordered_map<std::string, int> names;

                                Structure(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual Tajada::Type::Type * operator [] (int n) const;
                                virtual Tajada::Type::Type * operator [] (std::string const name) const;
                };

                class Tuple : public virtual Structure {
                        public:
                                Tuple(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Union : public virtual Structure {
                        public:
                                Union(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Array : public virtual Type {
                        public:
                                Type * contents;
                                unsigned int length;

                                Array(
                                        Type * p_contents
                                );

                                Array(
                                        Type * p_contents,
                                        unsigned int p_length
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                bool operator == (Type const &, Type const &);
                bool operator != (Type const &, Type const &);
        }
}

#endif
