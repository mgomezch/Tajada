#include <cassert>
#include <numeric>
#include <string>

#include "ast.hh"
#include "debug.hh"
#include "type.hh"
#include "util.hh"

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

namespace Tajada {
        namespace AST {
                Expression::Expression(Tajada::Type::Type * type):
                        type(type)
                {}

                AST::~AST() {}

                namespace Literal {
                        String::String(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Array(new Tajada::Type::Character())),
                                value(value)
                        {}

                        std::string String::show() {
                                return u8"“" + *value + u8"”";
                        }
/*
                        String::~String() {
        //                      delete dynamic_cast<Tajada::Type::Array *>(Tajada::AST::Expression::type)->contents;
        //                      delete type;
                        }
*/

                        Boolean::Boolean():
                                Tajada::AST::Expression(new Tajada::Type::Boolean())
                        {}

/*
                        Boolean::~Boolean() {
        //                      delete type;
                        }
*/

                        // ¿Por qué coño la llamada al constructor del padre indirecto no la puedo delegar al padre directo?
                        True ::True (): Tajada::AST::Expression(new Tajada::Type::Boolean()) {}
                        False::False(): Tajada::AST::Expression(new Tajada::Type::Boolean()) {}

                        std::string True::show() {
                                return std::string(u8"tetero");
                        }

                        std::string False::show() {
                                return std::string(u8"negrito");
                        }

                        Character::Character(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Character()),
                                value(new std::string(value->substr(1))) // FIXME: memory leak si no se libera en otro lado
                        {}

                        std::string Character::show() {
                                return
                                        std::string(u8"caraota(")
                                        + *value
                                        + std::string(u8")");
                        }

                        Integer::Integer(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Integer()),
                                value(0) // TODO: convert
                        {}

                        std::string Integer::show() {
                                return u8"queso(" + to_string(value) + u8")";
                        }

/*
                        Integer::~Integer() {
        //                      delete type;
                        }
*/

                        Float::Float(
                                std::string * integer,
                                std::string * fractional
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Character()),
                                value(0.0) // TODO: convert
                        {}

                        std::string Float::show() {
                                return u8"papelón(" + to_string(value) + u8")";
                        }

/*
                        Float::~Float() {
        //                      delete type;
                        }
*/

                        Tuple::Tuple(
                                std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * elems
                        ):
                                Tajada::AST::Expression(
                                        std::accumulate(
                                                (assert(elems != NULL), elems->begin()),
                                                (assert(elems != NULL), elems->end()),
                                                new Tajada::Type::Tuple(new std::list<std::tuple<Tajada::Type::Type *, std::string *> *>()),
                                                [](Tajada::Type::Tuple * acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                        acc->elems->push_back(new std::tuple<Tajada::Type::Type *, std::string *>(std::get<0>(*x)->type, std::get<1>(*x)));
                                                        return acc;
                                                }
                                        )
                                ),
                                elems(elems)
                        {}

                        std::string Tuple::show() {
                                return
                                        u8"«"
                                        + std::accumulate(
                                                elems->begin(),
                                                elems->end(),
                                                std::string(),
                                                [](std::string acc, std::tuple<Tajada::AST::Expression *, std::string *> * x) {
                                                        return
                                                                acc
                                                                + std::get<0>(*x)->show()
                                                                + [](std::string * x) {
                                                                        return *x == "" ? "" : " " + *x;
                                                                } (std::get<1>(*x));
                                                }
                                        )
                                        + u8"»";
                        }

/*
                        Tuple::~Tuple() {
        //                      delete type;
                        }
*/
                }

                TupleAccessByInteger::TupleAccessByInteger(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Literal::Integer * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[field->value]),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByInteger::show() {
                        return
                                source->show()
                                + u8" → "
                                + field->show();
                }

                TupleAccessByName::TupleAccessByName(
                        Tajada::AST::Expression * source,
                        std::string * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[*field]),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByName::show() {
                        return
                                source->show()
                                + u8" → "
                                + *field;
                }

                Variable::Variable(
                        std::string * name,
                        Tajada::Type::Type * type
                ):
                        name(name),
                        type(type)
                {}

                std::string Variable::show() {
                        return
                                *name
                                + u8" es "
                                + type->show()
                                + u8".";
                }
        }
}
