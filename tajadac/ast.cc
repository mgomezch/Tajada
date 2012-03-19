#include <numeric>
#include <string>

#include "ast.hh"
#include "debug.hh"
#include "type.hh"

#ifdef TAJADA_DEBUG
#       define TAJADA_DEBUG_AST TAJADA_DEBUG
#else
#       define TAJADA_DEBUG_AST 0
#endif

#if TAJADA_DEBUG_AST
#       define TAJADA_DEBUG_AST_PRINT(x) TAJADA_DEBUG_PRINT(AST, x)
#       define TAJADA_DEBUG_AST_DO(x) TAJADA_DEBUG_DO(AST, x)
#else
#       define TAJADA_DEBUG_AST_PRINT(x)
#       define TAJADA_DEBUG_AST_DO(x)
#endif

#define TAJADA_UNUSED_PARAMETER(p) static_cast<void>(p);

namespace Tajada {
        namespace AST {
                AST::~AST() {}

                Block::Block(
                        std::list<Tajada::AST::Statement *> * statements
                ):
                        statements(statements)
                {}

                std::string Block::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ') + u8"{\n"
                                + std::accumulate(
                                        statements->begin(),
                                        statements->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::Statement *statement) {
                                                return acc + statement->show(depth + 1);
                                        }
                                )
                                + std::string(depth * 8, ' ') + u8"}\n";
                }

                TypeAlias::TypeAlias(
                        std::string * name,
                        Tajada::Type::Type * type
                ):
                        name(name),
                        type(type)
                {}

                std::string TypeAlias::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + *name
                                + std::string(u8" es dulce de ")
                                + type->show(depth)
                                + std::string(u8".\n");
                }

                VariableDefinition::VariableDefinition(
                        std::string * name,
                        Tajada::Type::Type * type
                ):
                        name(name),
                        type(type)
                {}

                std::string VariableDefinition::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + *name
                                + std::string(u8" es ")
                                + type->show(depth)
                                + std::string(u8".\n");
                }

                FunctionDeclaration::FunctionDeclaration(
                        std::string * name,
                        Tajada::Type::Type * domain,
                        Tajada::Type::Type * codomain
                ):
                        name(name),
                        domain(domain),
                        codomain(codomain)
                {}

                std::string FunctionDeclaration::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + *name
                                + std::string(u8" es un plato de ")
                                + domain->show(depth)
                                + std::string(u8" y salsa de ")
                                + codomain->show(depth)
                                + std::string(u8".\n");
                }

                FunctionDefinition::FunctionDefinition(
                        std::string * name,
                        std::string * domain_name,
                        Tajada::Type::Type * domain,
                        Tajada::Type::Type * codomain,
                        Tajada::AST::Statement * body
                ):
                        name(name),
                        domain_name(domain_name),
                        domain(domain),
                        codomain(codomain),
                        body(body)
                {}

                std::string FunctionDefinition::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + *name
                                + std::string(u8" es un plato de ")
                                + domain->show(depth)
                                + (*domain_name == std::string("") ? std::string("") : std::string(u8" ") + *domain_name)
                                + std::string(u8" y salsa de ")
                                + codomain->show(depth)
                                + std::string(u8" ")
                                + body->show(depth)
                                + std::string(u8"\n");
                }

                Program::Program(
                                std::list<Tajada::AST::Statement *> * statements,
                                Tajada::AST::Block * main
                ):
                        statements(statements),
                        main(main)
                {}

                std::string Program::show(unsigned int depth) {
                        return
                                std::accumulate(
                                        statements->begin(),
                                        statements->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::Statement *statement) {
                                                return acc + statement->show(depth);
                                        }
                                )
                                + main->show(depth);
                }

                Expression::Expression(Tajada::Type::Type * type, bool is_lvalue):
                        type(type),
                        is_lvalue(is_lvalue)
                {}

                Argument::Argument(Tajada::Type::Type * type, bool is_lvalue):
                        type(type),
                        is_lvalue(is_lvalue)
                {}

                namespace Literal {
                        Boolean::Boolean(
                                bool p_value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Boolean(), false),
                                value(p_value)
                        {}

                        std::string Boolean::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return value ? std::string(u8"tetero") : std::string(u8"negrito");
                        }

                        Character::Character(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Character(), false),
                                value(value)
                        {}

                        std::string Character::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"caraota(")
                                        + *value
                                        + std::string(u8")");
                        }

                        String::String(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Array(new Tajada::Type::Character()), false),
                                value(value)
                        {}

                        std::string String::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"“")
                                        + *value
                                        + std::string(u8"”");
                        }

                        Integer::Integer(
                                std::string * p_value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Integer(), false),
                                value(stoi(*p_value))
                        {}

                        std::string Integer::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return std::to_string(value);
                        }

                        Float::Float(
                                std::string * p_integer,
                                std::string * p_fractional
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Float(), false),
                                value(stof(*p_integer + "." + *p_fractional))
                        {}

                        std::string Float::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"papelón(")
                                        + std::to_string(value)
                                        + std::string(u8")");
                        }

                        Tuple::Tuple(
                                std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems
                        ):
                                Tajada::AST::Expression(
                                        std::accumulate(
                                                elems->begin(),
                                                elems->end(),
                                                new Tajada::Type::Tuple(new std::list<std::tuple<Tajada::Type::Type *, std::string *> *>()),
                                                [](Tajada::Type::Tuple * acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                        acc->elems->push_back(new std::tuple<Tajada::Type::Type *, std::string *>(std::get<0>(*x)->type, std::get<1>(*x)));
                                                        return acc;
                                                }
                                        ),
                                        std::accumulate(
                                                elems->begin(),
                                                elems->end(),
                                                true,
                                                [](bool acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                        return acc && std::get<0>(*x)->is_lvalue;
                                                }
                                        )
                                ),
                                elems(elems)
                        {}

                        std::string Tuple::show(unsigned int depth) {
                                return
                                        std::string(u8"«")
                                        + std::accumulate(
                                                elems->begin(),
                                                --elems->end(),
                                                std::string(),
                                                [depth](std::string acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                        return
                                                                acc
                                                                + std::get<0>(*x)->show(depth)
                                                                + ", ";
                                                }
                                        )
                                        + (elems->size() == 0 ? "" : std::get<0>(*elems->back())->show(depth))
                                        + std::string(u8"»");
                        }
                }

                Call::Call(
                        std::string * name,
                        std::tuple<Tajada::Type::Type *, Tajada::Type::Type *, Tajada::AST::FunctionDefinition *> * data,
                        Tajada::AST::Expression * argument
                ):
                        Tajada::AST::Expression(std::get<1>(*data), false),
                        name(name),
                        data(data),
                        argument(argument)
                {}

                std::string Call::show(unsigned int depth) {
                        return
                                *name
                                + std::string(u8" @ ")
                                + argument->show(depth);
                }

                VariableUse::VariableUse(
                        std::string * name,
                        Tajada::Type::Type * type
                ):
                        Tajada::AST::Expression(type, true),
                        name(name)
                {}

                std::string VariableUse::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return *name;
                }

                TupleAccessByInteger::TupleAccessByInteger(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Literal::Integer * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[field->value], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByInteger::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + field->show(depth);
                }

                TupleAccessByName::TupleAccessByName(
                        Tajada::AST::Expression * source,
                        std::string * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[*field], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByName::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + *field;
                }

                ArrayAccess::ArrayAccess(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Expression * position
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Array &>(*source->type).contents, source->is_lvalue),
                        source(source),
                        position(position)
                {}

                std::string ArrayAccess::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8"[")
                                + position->show(depth)
                                + std::string(u8"]");
                }

                Sequence::Sequence(
                        Tajada::AST::Expression * first,
                        Tajada::AST::Expression * second
                ):
                        Tajada::AST::Expression(second->type, second->is_lvalue),
                        first(first),
                        second(second)
                {}

                std::string Sequence::show(unsigned int depth) {
                        return
                                first->show(depth)
                                + std::string(u8", ")
                                + second->show(depth);
                }

                ExpressionStatement::ExpressionStatement(
                        Tajada::AST::Expression * expression
                ):
                        expression(expression)
                {}

                std::string ExpressionStatement::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + expression->show(depth)
                                + std::string(u8".\n");
                }

                Assignment::Assignment(
                        Tajada::AST::Expression * lhs,
                        Tajada::AST::Expression * rhs
                ):
                        lhs(lhs),
                        rhs(rhs)
                {}

                std::string Assignment::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + lhs->show(depth)
                                + std::string(u8" ≔ ")
                                + rhs->show(depth)
                                + std::string(u8".\n");
                }

                If::If(
                        Tajada::AST::Expression * condition,
                        Tajada::AST::Statement * body_true,
                        Tajada::AST::Statement * body_false
                ):
                        condition(condition),
                        body_true(body_true),
                        body_false(body_false)
                {}

                std::string If::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + std::string(u8"if (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body_true->show(depth)
                                + std::string(u8" else ")
                                + body_false->show(depth)
                                + std::string(u8"\n");
                }

                While::While(
                        Tajada::AST::Expression * condition,
                        Tajada::AST::Statement * body
                ):
                        condition(condition),
                        body(body)
                {}

                std::string While::show(unsigned int depth) {
                        return
                                std::string(depth * 8, ' ')
                                + std::string(u8"while (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body->show(depth)
                                + std::string(u8"\n");
                }
        }
}
