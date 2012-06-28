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

namespace Tajada {
        namespace Builtins {
                std::pair<std::string, Builtins::descriptor> unary(
                        std::string          name,
                        Tajada::Type::Type * arg ,
                        Tajada::Type::Type * ret ,
                        std::function<
                                Tajada::Code::Intermediate::Instruction::Instruction * (
                                        Tajada::Code::Intermediate::Address::Temporary *,
                                        Tajada::Code::Intermediate::Address::Address   *
                                )
                        > constructor
                ) {
                        return std::make_pair(
                                name,
                                std::make_tuple(
                                        arg,
                                        ret,

                                        [constructor](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = c->argument->genr(b);
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(constructor(t, a));
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        );
                }

                std::pair<std::string, Builtins::descriptor> binary(
                        std::string          name,
                        Tajada::Type::Type * lhs ,
                        Tajada::Type::Type * rhs ,
                        Tajada::Type::Type * ret ,
                        std::function<
                                Tajada::Code::Intermediate::Instruction::Instruction * (
                                        Tajada::Code::Intermediate::Address::Temporary *,
                                        Tajada::Code::Intermediate::Address::Address   *,
                                        Tajada::Code::Intermediate::Address::Address   *
                                )
                        > constructor
                ) {
                        return std::make_pair(
                                name,
                                std::make_tuple(
                                        new Tajada::Type::Tuple(new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> ({
                                                new std::tuple<Tajada::Type::Type *, std::string *>(lhs, new std::string),
                                                new std::tuple<Tajada::Type::Type *, std::string *>(rhs, new std::string)
                                        })),

                                        ret,

                                        [constructor](Tajada::AST::Call * c, Tajada::Code::Block * b) {
                                                auto a = dynamic_cast<Tajada::Code::Intermediate::Address::Complex *>(c->argument->genr(b));
                                                auto t = new Tajada::Code::Intermediate::Address::Temporary();
                                                b->end->instructions.push_back(constructor(t, a->elems[0], a->elems[1]));
                                                return t;
                                        },

                                        static_cast<std::function<bool (Tajada::AST::Call *)>>(nullptr)
                                )
                        );
                }

#define TAJADA_BUILTINS_UNARY_CONSTRUCTOR(i)                        \
        [](                                                         \
                Tajada::Code::Intermediate::Address::Temporary * t, \
                Tajada::Code::Intermediate::Address::Address   * a  \
        ) { return new i(t, a); }

#define TAJADA_BUILTINS_UNARY(name, arg, ret, i)                   \
        unary(                                                     \
                name,                                              \
                new Tajada::Type::arg,                             \
                new Tajada::Type::ret,                             \
                TAJADA_BUILTINS_UNARY_CONSTRUCTOR(                 \
                        Tajada::Code::Intermediate::Instruction::i \
                )                                                  \
        )

#define TAJADA_BUILTINS_BINARY_CONSTRUCTOR(i)                        \
        [](                                                          \
                Tajada::Code::Intermediate::Address::Temporary * t , \
                Tajada::Code::Intermediate::Address::Address   * a0, \
                Tajada::Code::Intermediate::Address::Address   * a1  \
        ) { return new i(t, a0, a1); }

#define TAJADA_BUILTINS_BINARY(name, lhs, rhs, ret, i)             \
        binary(                                                    \
                name,                                              \
                new Tajada::Type::lhs,                             \
                new Tajada::Type::rhs,                             \
                new Tajada::Type::ret,                             \
                TAJADA_BUILTINS_BINARY_CONSTRUCTOR(                \
                        Tajada::Code::Intermediate::Instruction::i \
                )                                                  \
        )

                std::unordered_multimap<std::string, Builtins::descriptor> builtins {
                        TAJADA_BUILTINS_UNARY("negativo", Boolean, Boolean, Negate),
                        TAJADA_BUILTINS_UNARY("negativo", Integer, Integer, Negate),
                        TAJADA_BUILTINS_UNARY("negativo", Float  , Float  , Negate),

                        TAJADA_BUILTINS_BINARY("suma"          , Integer  , Integer  , Integer, Add      ),
                        TAJADA_BUILTINS_BINARY("suma"          , Float    , Float    , Float  , Add      ),
                        TAJADA_BUILTINS_BINARY("resta"         , Integer  , Integer  , Integer, Substract),
                        TAJADA_BUILTINS_BINARY("resta"         , Float    , Float    , Float  , Substract),
                        TAJADA_BUILTINS_BINARY("multiplicación", Integer  , Integer  , Integer, Multiply ),
                        TAJADA_BUILTINS_BINARY("multiplicación", Float    , Float    , Float  , Multiply ),
                        TAJADA_BUILTINS_BINARY("división"      , Integer  , Integer  , Integer, Divide   ),
                        TAJADA_BUILTINS_BINARY("división"      , Float    , Float    , Float  , Divide   ),
                        TAJADA_BUILTINS_BINARY("módulo"        , Integer  , Integer  , Integer, Modulo   ),
                        TAJADA_BUILTINS_BINARY("or"            , Boolean  , Boolean  , Boolean, Or       ),
                        TAJADA_BUILTINS_BINARY("and"           , Boolean  , Boolean  , Boolean, And      ),
                        TAJADA_BUILTINS_BINARY("menor"         , Integer  , Integer  , Boolean, LessThan ),
                        TAJADA_BUILTINS_BINARY("menor"         , Float    , Float    , Boolean, LessThan ),
                        TAJADA_BUILTINS_BINARY("menor"         , Character, Character, Boolean, LessThan ),
                        TAJADA_BUILTINS_BINARY("igualdad"      , Integer  , Integer  , Boolean, Equal    ),
                        TAJADA_BUILTINS_BINARY("igualdad"      , Float    , Float    , Boolean, Equal    ),
                        TAJADA_BUILTINS_BINARY("igualdad"      , Boolean  , Boolean  , Boolean, Equal    ),
                        TAJADA_BUILTINS_BINARY("igualdad"      , Character, Character, Boolean, Equal    ),
                };

#undef TAJADA_BUILTINS_BINARY
#undef TAJADA_BUILTINS_BINARY_CONSTRUCTOR
#undef TAJADA_BUILTINS_UNARY
#undef TAJADA_BUILTINS_UNARY_CONSTRUCTOR
        }
}
