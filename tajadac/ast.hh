#ifndef TAJADA_AST_HH
#define TAJADA_AST_HH

#include <string>

#include "type.hh"

namespace Tajada {
        namespace AST {
                class Expression {
                        public:
                                Tajada::Type::Type * type;

                                Expression(Tajada::Type::Type * type = NULL);

                                virtual std::string show() = 0;

                                virtual ~Expression() = 0;
                };

                namespace Literal {
                        class Boolean : public virtual Tajada::AST::Expression {
                                public:
                                        Boolean();

//                                      virtual ~Boolean();
                        };

                        class True : public virtual Boolean {
                                virtual std::string show();
                        };

                        class False : public virtual Boolean {
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

                                        Tuple(std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems = NULL);

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
        }
}

#endif
