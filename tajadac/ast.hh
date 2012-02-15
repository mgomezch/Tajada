#ifndef TAJADA_AST_HH
#define TAJADA_AST_HH

#include <string>

#include "type.hh"

namespace Tajada {
        namespace AST {
                class AST {
                        public:
                                virtual std::string show() = 0;

                                virtual ~AST() = 0;
                };

                class Expression : public virtual Tajada::AST::AST {
                        public:
                                Tajada::Type::Type * type;

                                Expression(Tajada::Type::Type * type);
                };

                namespace Literal {
                        class Boolean : public virtual Tajada::AST::Expression {
                                public:
                                        Boolean();

//                                      virtual ~Boolean();
                        };

                        class True : public virtual Boolean {
                                public:
                                        True();

                                        virtual std::string show();
                        };

                        class False : public virtual Boolean {
                                public:
                                        False();

                                        virtual std::string show();
                        };

                        class Character : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        Character(std::string * value);

                                        virtual std::string show();
                        };

                        class String : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        String(std::string * value);

                                        virtual std::string show();

//                                      virtual ~String();
                        };

                        class Integer : public virtual Tajada::AST::Expression {
                                public:
                                        int value;

                                        Integer(std::string * value);

                                        virtual std::string show();

//                                      virtual ~Integer();
                        };

                        class Float : public virtual Tajada::AST::Expression {
                                public:
                                        float value;

                                        Float(std::string * integer, std::string * fractional);

                                        virtual std::string show();

//                                      virtual ~Float();
                        };

                        class Tuple : public virtual Tajada::AST::Expression {
                                public:
                                        std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems;

                                        Tuple(std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems);

                                        virtual std::string show();

//                                      virtual ~Tuple();
                        };
                }

                class TupleAccessByInteger : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Literal::Integer * field;

                                TupleAccessByInteger(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Literal::Integer * field
                                );

                                virtual std::string show();
                };

                class TupleAccessByName : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                std::string * field;

                                TupleAccessByName(
                                        Tajada::AST::Expression * source,
                                        std::string * field
                                );

                                virtual std::string show();
                };

                class Variable : public virtual Tajada::AST::AST {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                Variable(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show();
                };
        }
}

#endif
