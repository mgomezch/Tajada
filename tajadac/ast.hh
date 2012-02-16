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

                class Statement : public virtual Tajada::AST::AST {};

                class Block : public virtual Tajada::AST::Statement {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;

                                Block(
                                        std::list<Tajada::AST::Statement *> * statements
                                );

                                virtual std::string show();
                };

                class TypeAlias : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                TypeAlias(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show();
                };

                class VariableDefinition : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                VariableDefinition(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show();
                };

                class FunctionDeclaration : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * domain;
                                Tajada::Type::Type * codomain;

                                FunctionDeclaration(
                                        std::string * name,
                                        Tajada::Type::Type * domain,
                                        Tajada::Type::Type * codomain
                                );

                                virtual std::string show();
                };

                class FunctionDefinition : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                std::string * domain_name;
                                Tajada::Type::Type * domain;
                                Tajada::Type::Type * codomain;
                                Tajada::AST::Block * body;

                                FunctionDefinition(
                                        std::string * name,
                                        std::string * domain_name,
                                        Tajada::Type::Type * domain,
                                        Tajada::Type::Type * codomain,
                                        Tajada::AST::Block * body
                                );

                                virtual std::string show();
                };

                class Program : public virtual Tajada::AST::AST {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;
                                Tajada::AST::Block * main;

                                Program(
                                        std::list<Tajada::AST::Statement *> * statements,
                                        Tajada::AST::Block * main
                                );

                                virtual std::string show();
                };

                class Expression : public virtual Tajada::AST::AST {
                        public:
                                Tajada::Type::Type * type;
                                bool lvalue;

                                Expression(Tajada::Type::Type * type, bool lvalue);
                };

                namespace Literal {
                        class Boolean : public virtual Tajada::AST::Expression {
                                public:
                                        Boolean();
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
                        };

                        class Integer : public virtual Tajada::AST::Expression {
                                public:
                                        int value;

                                        Integer(std::string * value);

                                        virtual std::string show();
                        };

                        class Float : public virtual Tajada::AST::Expression {
                                public:
                                        float value;

                                        Float(std::string * integer, std::string * fractional);

                                        virtual std::string show();
                        };

                        class Tuple : public virtual Tajada::AST::Expression {
                                public:
                                        std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems;

                                        Tuple(std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems);

                                        virtual std::string show();
                        };
                }

                class Call : public virtual Tajada::AST::Expression {
                        public:
                                std::string * name;
                                std::tuple<Tajada::Type::Type *, Tajada::Type::Type *, Tajada::AST::FunctionDefinition *> * data;
                                Tajada::AST::Expression * argument;

                                Call(
                                        std::string * name,
                                        std::tuple<Tajada::Type::Type *, Tajada::Type::Type *, Tajada::AST::FunctionDefinition *> * data,
                                        Tajada::AST::Expression * argument
                                );

                                virtual std::string show();
                };

                class VariableUse : public virtual Tajada::AST::Expression {
                        public:
                                std::string * name;

                                VariableUse(std::string * name, Tajada::Type::Type * type);

                                virtual std::string show();
                };

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

                class ArrayAccess : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Expression * position;

                                ArrayAccess(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Expression * position
                                );

                                virtual std::string show();
                };

                class Sequence : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * first;
                                Tajada::AST::Expression * second;

                                Sequence(
                                        Tajada::AST::Expression * first,
                                        Tajada::AST::Expression * second
                                );

                                virtual std::string show();
                };

                class ExpressionStatement : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * expression;

                                ExpressionStatement(
                                        Tajada::AST::Expression * expression
                                );

                                virtual std::string show();
                };

                class Assignment : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * lhs;
                                Tajada::AST::Expression * rhs;

                                Assignment(
                                        Tajada::AST::Expression * lhs,
                                        Tajada::AST::Expression * rhs
                                );

                                virtual std::string show();
                };

                class If : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * condition;
                                Tajada::AST::Statement * body_true;
                                Tajada::AST::Statement * body_false;

                                If(
                                        Tajada::AST::Expression * condition,
                                        Tajada::AST::Statement * body_true,
                                        Tajada::AST::Statement * body_false
                                );

                                virtual std::string show();
                };

                class While : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * condition;
                                Tajada::AST::Statement * body;

                                While(
                                        Tajada::AST::Expression * condition,
                                        Tajada::AST::Statement * body
                                );

                                virtual std::string show();
                };
        }
}

#endif
