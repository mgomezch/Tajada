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

#ifndef TAJADA_UNUSED_PARAMETER
#       define TAJADA_UNUSED_PARAMETER(p) static_cast<void>(p);
#endif

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
                                std::string(u8"{\n")
                                + std::accumulate(
                                        statements->begin(),
                                        statements->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::Statement *statement) {
                                                return
                                                        acc
                                                        + std::string((depth + 1) * 8, ' ')
                                                        + statement->show(depth + 1)
                                                        + (
                                                                (
                                                                        dynamic_cast<Block *>(statement)
                                                                        || dynamic_cast<If *>(statement)
                                                                        || dynamic_cast<While *>(statement)
                                                                        || dynamic_cast<For *>(statement)
                                                                        || dynamic_cast<TypeSelection *>(statement)
                                                                )
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        );
                                        }
                                )
                                + std::string(depth * 8, ' ')
                                + u8"}";
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
                                *name
                                + std::string(u8" es dulce de ")
                                + type->show(depth);
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
                                *name
                                + std::string(u8" es ")
                                + type->show(depth);
                }

                FunctionDeclaration::FunctionDeclaration(
                        std::string * name,
                        std::string * domain_name,
                        Tajada::Type::Type * domain,
                        Tajada::Type::Type * codomain
                ):
                        name(name),
                        domain_name(domain_name),
                        domain(domain),
                        codomain(codomain)
                {}

                std::string FunctionDeclaration::show(unsigned int depth) {
                        return
                                *name
                                + std::string(u8" es un plato de ")
                                + domain->show(depth)
                                + u8" "
                                + *domain_name
                                + std::string(u8" y salsa de ")
                                + codomain->show(depth);
                }

                Function::Function(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        declaration(p_declaration),
                        evaluator(p_evaluator)
                {}

                std::string Function::show(unsigned int depth) {
                        return declaration->show(depth);
                }

                BuiltinFunction::BuiltinFunction(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        Tajada::AST::Function(p_declaration, p_evaluator)
                {}

                std::string BuiltinFunction::show(unsigned int depth) {
                        return
                                Function::show(depth)
                                + u8" (builtin"
                                + (evaluator != nullptr ? u8", constexpr" : "")
                                + u8")";
                }

                FunctionDefinition::FunctionDefinition(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        Tajada::AST::Statement * p_body,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        Tajada::AST::Function(p_declaration, p_evaluator),
                        body(p_body)
                {}

                std::string FunctionDefinition::show(unsigned int depth) {
                        return
                                Function::show(depth)
                                + u8" "
                                + body->show(depth)
                                + u8"\n";
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
                                                return
                                                        acc
                                                        + statement->show(depth)
                                                        + (
                                                                (dynamic_cast<Block *>(statement) || dynamic_cast<FunctionDefinition *>(statement))
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        );
                                        }
                                )
                                + main->show(depth);
                }

                Expression::Expression(
                        Tajada::Type::Type * p_type,
                        bool p_is_lvalue
                ):
                        type(p_type),
                        is_lvalue(p_is_lvalue)
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
                                return value ? std::string(u8"negrito") : std::string(u8"tetero");
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
                                std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems
                        ):
                                Tajada::AST::Expression(
                                        new Tajada::Type::Tuple(
                                                std::accumulate(
                                                        elems->begin(),
                                                        elems->end(),
                                                        new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>(),
                                                        [](
                                                                std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * acc,
                                                                std::tuple<Tajada::AST::Expression *, std::string *> * x
                                                        ) {
                                                                acc->push_back(
                                                                        new std::tuple<Tajada::Type::Type *, std::string *>(
                                                                                std::get<0>(*x)->type,
                                                                                std::get<1>(*x)
                                                                        )
                                                                );
                                                                return acc;
                                                        }
                                                )
                                        ),
                                        std::accumulate(
                                                elems->begin(),
                                                elems->end(),
                                                true,
                                                [](
                                                        bool acc,
                                                        std::tuple<Tajada::AST::Expression *, std::string *> * x
                                                ) {
                                                        return acc && std::get<0>(*x)->is_lvalue;
                                                }
                                        )
                                ),
                                elems(elems)
                        {}

                        std::string Tuple::show(unsigned int depth) {
                                return
                                        std::string(u8"«")
                                        + (elems->size() == 0 ? "" :
                                                std::accumulate(
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
                                        )
                                        + (elems->size() == 0 ? "" : std::get<0>(*elems->back())->show(depth))
                                        + std::string(u8"»");
                        }
                }

                Call::Call(
                        std::string * p_name,
                        Tajada::AST::Function ** p_definition_ptr,
                        Tajada::AST::Expression * p_argument,
                        Tajada::Type::Type * p_return_type
                ):
                        Tajada::AST::Expression(p_return_type, false),
                        name(p_name),
                        definition_ptr(p_definition_ptr),
                        argument(p_argument)
                {}

                std::string Call::show(unsigned int depth) {
                        return
                                *name
                                + u8" $ "
                                + argument->show(depth);
                }

                VariableUse::VariableUse(
                        unsigned int p_scope_id,
                        std::string * p_name,
                        Tajada::Type::Type * p_type
                ):
                        Tajada::AST::Expression(p_type, true),
                        scope_id(p_scope_id),
                        name(p_name)
                {}

                std::string VariableUse::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return
                                *name
                                + u8"[[scope: "
                                + std::to_string(scope_id)
                                + u8"]]";
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

                UnionAccessByInteger::UnionAccessByInteger(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Literal::Integer * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Union &>(*source->type)[field->value], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string UnionAccessByInteger::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + field->show(depth);
                }

                UnionAccessByName::UnionAccessByName(
                        Tajada::AST::Expression * source,
                        std::string * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Union &>(*source->type)[*field], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string UnionAccessByName::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" ⇒ ")
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
                                expression->show(depth);
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
                                lhs->show(depth)
                                + std::string(u8" ≔ ")
                                + rhs->show(depth);
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
                                std::string(u8"if (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body_true->show(depth)
                                + (
                                        (
                                                dynamic_cast<Block *>(body_true)
                                                || dynamic_cast<If *>(body_true)
                                                || dynamic_cast<While *>(body_true)
                                                || dynamic_cast<For *>(body_true)
                                                || dynamic_cast<TypeSelection *>(body_true)
                                        )
                                        ? (
                                                body_false
                                                ? u8" "
                                                : u8""
                                        )
                                        : (u8".\n" + (body_false ? std::string(depth * 8, ' ') : u8""))
                                )
                                + (
                                        body_false
                                        ? std::string(u8"else ")
                                        + body_false->show(depth)
                                        + (
                                                (
                                                        dynamic_cast<Block *>(body_false)
                                                        || dynamic_cast<If *>(body_false)
                                                        || dynamic_cast<While *>(body_false)
                                                        || dynamic_cast<For *>(body_false)
                                                        || dynamic_cast<TypeSelection *>(body_false)
                                                )
                                                ? u8""
                                                : u8"."
                                        )
                                        : u8""
                                );
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
                                std::string(u8"while (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body->show(depth)
                                + std::string(u8"\n");
                }

                For::For(
                        std::string * p_counter,
                        Tajada::AST::Expression * p_inicio,
                        Tajada::AST::Expression * p_fin,
                        Tajada::AST::Statement * p_body
                ):
                        counter(p_counter),
                        inicio(p_inicio),
                        fin(p_fin),
                        body(p_body)
                {}

                std::string For::show(unsigned int depth) {
                        return
                                u8"for "
                                + *counter
                                + u8" in ("
                                + inicio->show(depth)
                                + u8" … "
                                + fin->show(depth)
                                + u8") "
                                + body->show(depth)
                                + (
                                        (
                                                dynamic_cast<Block *>(body)
                                                || dynamic_cast<If *>(body)
                                                || dynamic_cast<While *>(body)
                                                || dynamic_cast<For *>(body)
                                                || dynamic_cast<TypeSelection *>(body)
                                        )
                                        ? u8""
                                        : u8"."
                                );
                }

                namespace TypeCase {
                        TypeCase::TypeCase(
                                Tajada::AST::Statement * p_body
                        ):
                                body(p_body)
                        {}

                        Integer::Integer(
                                std::string * p_index,
                                Tajada::AST::Statement * p_body
                        ):
                                TypeCase(p_body),
                                index(stoi(*p_index))
                        {}

                        std::string Integer::show(unsigned int depth) {
                                return
                                        std::to_string(index)
                                        + u8" ∶ "
                                        + body->show(depth);
                        }

                        String::String(
                                std::string * p_index,
                                Tajada::AST::Statement * p_body
                        ):
                                TypeCase(p_body),
                                index(p_index)
                        {}

                        std::string String::show(unsigned int depth) {
                                return
                                        *index
                                        + u8" ∶ "
                                        + body->show(depth);
                        }
                }

                TypeSelection::TypeSelection(
                        Tajada::AST::Expression * p_fuente,
                        std::string * p_variable,
                        std::vector<Tajada::AST::TypeCase::TypeCase *> * p_casos
                ):
                        fuente(p_fuente),
                        variable(p_variable),
                        casos(p_casos)
                {}

                std::string TypeSelection::show(unsigned int depth) {
                        return
                                fuente->show(depth)
                                + u8" ∷ "
                                + *variable
                                + u8" {\n"
                                + std::accumulate(
                                        casos->begin(),
                                        casos->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::TypeCase::TypeCase * c) {
                                                return
                                                        acc
                                                        + std::string((depth + 1) * 8, ' ')
                                                        + c->show(depth + 1)
                                                        + (
                                                                (
                                                                        dynamic_cast<Block *>(c->body)
                                                                        || dynamic_cast<If *>(c->body)
                                                                        || dynamic_cast<While *>(c->body)
                                                                        || dynamic_cast<For *>(c->body)
                                                                        || dynamic_cast<TypeSelection *>(c->body)
                                                                )
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        );
                                        }
                                )
                                + std::string(depth * 8, ' ')
                                + u8"}";
                }

                Return::Return(
                        Tajada::AST::Expression * expression
                ):
                        expression(expression)
                {}

                std::string Return::show(unsigned int depth) {
                        return
                                u8"retorna "
                                + expression->show(depth);
                }

                Break::Break(
                        Tajada::AST::Statement * p_statement
                ):
                        statement(p_statement)
                {}

                std::string Break::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return
                                u8"break";
                }
        }
}
