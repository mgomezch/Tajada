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

                                Type(
                                        Complete p_is_complete
                                );

                                virtual unsigned int size();
                                virtual unsigned int alignment();

                                virtual std::string show(unsigned int depth = 0) = 0;

                                virtual ~Type() = 0;

                        protected:
                                bool has_saved_size;
                                unsigned int saved_size;

                                bool has_saved_alignment;
                                unsigned int saved_alignment;

                                virtual unsigned int size_()      = 0;
                                virtual unsigned int alignment_() = 0;
                };

                class Boolean : public virtual Type {
                        public:
                                Boolean();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };

                class Character : public virtual Type {
                        public:
                                Character();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };

                class Integer : public virtual Type {
                        public:
                                Integer();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };

                class Float : public virtual Type {
                        public:
                                Float();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
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

                                virtual unsigned int alignment_();
                };

                class Tuple : public virtual Structure {
                        public:
                                Tuple(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual unsigned int size_();
                                virtual std::string show(unsigned int depth = 0);
                };

                class Union : public virtual Structure {
                        public:
                                Union(
                                        std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * elems
                                );

                                virtual unsigned int size_();
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

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };

                class Reference : public virtual Type {
                        public:
                                Type * target;

                                Reference(
                                        Type * p_target
                                );

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };

                bool operator == (Type const &, Type const &);
                bool operator != (Type const &, Type const &);
        }
}

#endif
