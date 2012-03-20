#ifndef TAJADA_AST_HH
#define TAJADA_AST_HH

#include <list>
#include <string>

#include "type.hh"

namespace Tajada {
        namespace AST {
                enum class Operator : unsigned int {
                        minus,
                        plus,
                        mult,
                        div,
                        mod,
                        eq,
                        neq
                };

                class AST {
                        public:
                                virtual std::string show(unsigned int depth = 0) = 0;

                                virtual ~AST() = 0;
                };

                class Statement : public virtual Tajada::AST::AST {};

                class Block : public virtual Tajada::AST::Statement {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;

                                Block(
                                        std::list<Tajada::AST::Statement *> * statements
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class TypeAlias : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                TypeAlias(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class VariableDefinition : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                VariableDefinition(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class FunctionDeclaration : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                std::string * domain_name;
                                Tajada::Type::Type * domain;
                                Tajada::Type::Type * codomain;

                                FunctionDeclaration(
                                        std::string * name,
                                        std::string * domain_name,
                                        Tajada::Type::Type * domain,
                                        Tajada::Type::Type * codomain
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class FunctionDefinition : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                std::string * domain_name;
                                Tajada::Type::Type * domain;
                                Tajada::Type::Type * codomain;
                                Tajada::AST::Statement * body;

                                FunctionDefinition(
                                        std::string * name,
                                        std::string * domain_name,
                                        Tajada::Type::Type * domain,
                                        Tajada::Type::Type * codomain,
                                        Tajada::AST::Statement * body
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Program : public virtual Tajada::AST::AST {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;
                                Tajada::AST::Block * main;

                                Program(
                                        std::list<Tajada::AST::Statement *> * statements,
                                        Tajada::AST::Block * main
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Expression : public virtual Tajada::AST::AST {
                        public:
                                Tajada::Type::Type * type;
                                bool is_lvalue;

                                Expression(
                                        Tajada::Type::Type * type,
                                        bool is_lvalue
                                );
                };

                namespace Literal {
                        class Boolean : public virtual Tajada::AST::Expression {
                                public:
                                        bool value;

                                        Boolean(
                                                bool p_value
                                        );

                                        virtual std::string show(unsigned int depth = 0);
                        };

                        class Character : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        Character(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };

                        class String : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        String(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };

                        class Integer : public virtual Tajada::AST::Expression {
                                public:
                                        int value;

                                        Integer(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };

                        class Float : public virtual Tajada::AST::Expression {
                                public:
                                        float value;

                                        Float(std::string * integer, std::string * fractional);

                                        virtual std::string show(unsigned int depth = 0);
                        };

                        class Tuple : public virtual Tajada::AST::Expression {
                                public:
                                        std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems;

                                        Tuple(std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems);

                                        virtual std::string show(unsigned int depth = 0);
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

                                virtual std::string show(unsigned int depth = 0);
                };

                class VariableUse : public virtual Tajada::AST::Expression {
                        public:
                                std::string * name;

                                VariableUse(std::string * name, Tajada::Type::Type * type);

                                virtual std::string show(unsigned int depth = 0);
                };

                class TupleAccessByInteger : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Literal::Integer * field;

                                TupleAccessByInteger(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Literal::Integer * field
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class TupleAccessByName : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                std::string * field;

                                TupleAccessByName(
                                        Tajada::AST::Expression * source,
                                        std::string * field
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class ArrayAccess : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Expression * position;

                                ArrayAccess(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Expression * position
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Sequence : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * first;
                                Tajada::AST::Expression * second;

                                Sequence(
                                        Tajada::AST::Expression * first,
                                        Tajada::AST::Expression * second
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class ExpressionStatement : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * expression;

                                ExpressionStatement(
                                        Tajada::AST::Expression * expression
                                );

                                virtual std::string show(unsigned int depth = 0);
                };

                class Assignment : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * lhs;
                                Tajada::AST::Expression * rhs;

                                Assignment(
                                        Tajada::AST::Expression * lhs,
                                        Tajada::AST::Expression * rhs
                                );

                                virtual std::string show(unsigned int depth = 0);
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

                                virtual std::string show(unsigned int depth = 0);
                };

                class While : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * condition;
                                Tajada::AST::Statement * body;

                                While(
                                        Tajada::AST::Expression * condition,
                                        Tajada::AST::Statement * body
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
