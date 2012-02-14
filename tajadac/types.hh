#ifndef TAJADA_TYPES_HH
#define TAJADA_TYPES_HH

#include <list>
#include <string>
#include <tuple>

namespace Tajada {
        namespace types {
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
                                std::list<std::tuple<Type *, std::string>> elems;

                                virtual std::string show();
                };

                class Union : public virtual Type {
                        public:
                                std::list<std::tuple<Type *, std::string>> elems;

                                virtual std::string show();
                };

                class Array : public virtual Type {
                        public:
                                Type * contents;

                                virtual std::string show();
                };

                bool operator == (Type &, Type &);
                bool operator != (Type &, Type &);

        }
}

#endif
