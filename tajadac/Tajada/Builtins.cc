#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "Tajada/Builtins.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Address/Complex.hh"
#include "Tajada/Code/Intermediate/Instruction/Add.hh"
#include "Tajada/Code/Intermediate/Instruction/And.hh"
#include "Tajada/Code/Intermediate/Instruction/Divide.hh"
#include "Tajada/Code/Intermediate/Instruction/Equal.hh"
#include "Tajada/Code/Intermediate/Instruction/LessThan.hh"
#include "Tajada/Code/Intermediate/Instruction/Modulo.hh"
#include "Tajada/Code/Intermediate/Instruction/Multiply.hh"
#include "Tajada/Code/Intermediate/Instruction/Negate.hh"
#include "Tajada/Code/Intermediate/Instruction/Or.hh"
#include "Tajada/Code/Intermediate/Instruction/Substract.hh"
#include "Tajada/Type/Integer.hh"
#include "Tajada/Type/Tuple.hh"
#include "Tajada/Type/Type.hh"

// This is the ugliest code in the history of humanity.  I’m aware.  I’ll turn it into something trivial and tiny once I have the time.  Copy/paste just happened to be faster than preprocessor magic and this is due two hours ago.
namespace Tajada {
        namespace Builtins {
                std::unordered_multimap<
                        std::string,
                        std::tuple<
                                Tajada::Type::Type                        *,
                                Tajada::Type::Type                        *,
                                Tajada::Builtins::generator                ,
                                std::function<bool (Tajada::AST::Call *)>
                        >
                > builtins {
                        std::make_pair(
                                std::string(u8"negativo"),
                                std::make_tuple(
                                        new Tajada::Type::Integer,

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = c->argument->genr(b);
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Negate(t, a)
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"negativo"),
                                std::make_tuple(
                                        new Tajada::Type::Boolean,

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = c->argument->genr(b);
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Negate(t, a)
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"suma"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Add(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"suma"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Float,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Add(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"resta"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Substract(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"resta"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Float,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Substract(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"multiplicación"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Multiply(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"multiplicación"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Float,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Multiply(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"división"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Divide(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"división"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Float,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Divide(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"módulo"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Integer,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Modulo(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"módulo"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Float,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Modulo(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"or"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Or(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"and"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::And(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"menor"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::LessThan(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"menor"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::LessThan(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"igualdad"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Integer, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Equal(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"igualdad"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Float, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Equal(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"igualdad"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Boolean, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Equal(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        ),



                        std::make_pair(
                                std::string(u8"igualdad"),
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Character, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(new Tajada::Type::Character, new std::string)
                                        })),

                                        new Tajada::Type::Boolean,

                                        [](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(
                                                        new Tajada::Code::Intermediate::Instruction::Equal(t, a->elems[0], a->elems[1])
                                                );
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        )
                };
        }
}
