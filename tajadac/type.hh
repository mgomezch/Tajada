#ifndef TAJADA_TYPES_HH
#define TAJADA_TYPES_HH

#include <list>
#include <string>
#include <tuple>

namespace Tajada {
        namespace Type {
                class Type {
                        public:
                                virtual std::string show() = 0;

                                virtual ~Type() = 0;
                };

                class Boolean : public virtual Type {
                        public:
                                virtual std::string show();
                };

                class Character : public virtual Type {
                        public:
                                virtual std::string show();
                };

                class Integer : public virtual Type {
                        public:
                                virtual std::string show();
                };

                class Float : public virtual Type {
                        public:
                                virtual std::string show();
                };

                class Tuple : public virtual Type {
                        public:
                                std::list<std::tuple<Tajada::Type::Type *, std::string *> *> * elems;

                                Tuple(std::list<std::tuple<Tajada::Type::Type *, std::string *> *> * elems);

                                Tajada::Type::Type * operator [] (int n) const;
                                Tajada::Type::Type * operator [] (std::string const name) const;

                                virtual std::string show();
                };

                class Union : public virtual Type {
                        public:
                                std::list<std::tuple<Tajada::Type::Type *, std::string *> *> * elems;

                                virtual std::string show();
                };

                class Array : public virtual Type {
                        public:
                                Type * contents;

                                Array(Type * contents);

                                virtual std::string show();
                };

                bool operator == (Type const &, Type const &);
                bool operator != (Type const &, Type const &);
        }
}

#endif
