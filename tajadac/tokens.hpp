#ifndef TAJADA_TOKENS_HPP_
#define TAJADA_TOKENS_HPP_

#define ENDLINES "\u000A\u000B\u000C\u000D\u0085\u2028\u2029"

#define RESERVED_WORD(TOKEN, tag, word)                 \
        TOKEN(                                          \
                tag,                                    \
                u8"palabra reservada “" word u8"”",     \
                u8"(" word u8")"                        \
        )

#define TOKEN_DATA(TOKEN)                                                      \
        /* §1.1p7 */                                                           \
        TOKEN(                                                                 \
                LIT_STR,                                                       \
                u8"literal de cadena de caracteres",                           \
                u8R"#((“([^”\\]|\\.)*”))#"                                     \
        )                                                                      \
                                                                               \
        /* §1.2 */                                                             \
        TOKEN(                                                                 \
                IGNORE,                                                        \
                u8"espacio en blanco",                                         \
                u8"(("                                                         \
                        /* §1.2.1p4 (comentario de bloque) */                  \
                        u8"‹[^›]*›|"                                           \
                                                                               \
                        /* §1.2.2p4 (comentario de línea */                    \
                        u8"⫽[^" ENDLINES u8"]*"                                \
                        u8"["   ENDLINES u8"]|"                                \
                                                                               \
                        /* §1.2.2p5 (fin de línea) */                          \
                        u8"\u000A|"                                            \
                        u8"\u000B|"                                            \
                        u8"\u000C|"                                            \
                        u8"\u000D|"                                            \
                        u8"\u0085|"                                            \
                        u8"\u2028|"                                            \
                        u8"\u2029|"                                            \
                                                                               \
                        /* §1.2.3p1 (espacio en blanco individual) */          \
                        /* Taken from the PropList.txt file in the Unicode  */ \
                        /* Character Database, version 6.0.0 (lines 11–22). */ \
                        /* re2 does not currently support the White_Space   */ \
                        /* property, so "\\p{WS}" won’t work. :(            */ \
                        u8"["                                                  \
                                u8"\u0009-\u000D"                              \
                                u8"\u0020"                                     \
                                u8"\u0085"                                     \
                                u8"\u00A0"                                     \
                                u8"\u1680"                                     \
                                u8"\u180E"                                     \
                                u8"\u2000-\u200A"                              \
                                u8"\u2028"                                     \
                                u8"\u2029"                                     \
                                u8"\u202F"                                     \
                                u8"\u205F"                                     \
                                u8"\u3000"                                     \
                        u8"]"                                                  \
                u8")+)"                                                        \
        )                                                                      \
                                                                               \
        /* §1.3.1p2 */                                                         \
        TOKEN(                                                                 \
                LIT_INT,                                                       \
                u8"literal entero",                                            \
                u8R"#(([0-9]+))#"                                              \
        )                                                                      \
                                                                               \
        /* §1.3.2p1 */                                                         \
        TOKEN(                                                                 \
                FLOAT_SEP,                                                     \
                u8"separador de literal de punto flotante",                    \
                u8R"#((·))#"                                                   \
        )                                                                      \
                                                                               \
        /* §2.1.1p1 */                                                         \
        RESERVED_WORD(TOKEN, TETERO , u8"tetero" )                             \
                                                                               \
        /* §2.1.1p2 */                                                         \
        RESERVED_WORD(TOKEN, NEGRITO, u8"negrito")                             \
                                                                               \
        /* §2.1.1p3 */                                                         \
        RESERVED_WORD(TOKEN, CAFE   , u8"café"   )                             \
                                                                               \
        /* §2.1.2p1 */                                                         \
        RESERVED_WORD(TOKEN, CARAOTA, u8"caraota")                             \
                                                                               \
        /* §1.1p4, §2.1.2p3 */                                                 \
        TOKEN(                                                                 \
                LIT_CHR,                                                       \
                u8"literal de caraota",                                        \
                u8R"#((\\.))#"                                                 \
        )                                                                      \
                                                                               \
        /* §2.1.3p1 */                                                         \
        RESERVED_WORD(TOKEN, QUESO, u8"queso")                                 \
                                                                               \
        /* §2.2p3 */                                                           \
        RESERVED_WORD(TOKEN, AREPA, u8"arepa")                                 \
                                                                               \
        /* §2.2p4 */                                                           \
        RESERVED_WORD(TOKEN, SOLA , u8"sola" )                                 \
                                                                               \
        /* §2.2p5 */                                                           \
        RESERVED_WORD(TOKEN, DE   , u8"de"   )                                 \
                                                                               \
        /* §2.2p6 */                                                           \
        RESERVED_WORD(TOKEN, CON  , u8"con"  )                                 \
                                                                               \
        /* §2.2p9 */                                                           \
        TOKEN(                                                                 \
                SEP_LIST,                                                      \
                u8"separador de lista",                                        \
                u8R"#((,))#"                                                   \
        )                                                                      \
                                                                               \
        /* §2.2p10 */                                                          \
        RESERVED_WORD(TOKEN, Y      , u8"y"      )                             \
                                                                               \
        /* §2.3p4 */                                                           \
        RESERVED_WORD(TOKEN, CACHAPA, u8"cachapa")                             \
                                                                               \
        /* §2.3p5 */                                                           \
        RESERVED_WORD(TOKEN, O      , u8"o"      )                             \
                                                                               \
        /* §2.4p2 */                                                           \
        RESERVED_WORD(TOKEN, ARROZ  , u8"arroz"  )                             \
                                                                               \
        /* §3.1.1p1 */                                                         \
        RESERVED_WORD(TOKEN, ES     , u8"es"     )                             \
                                                                               \
        /* §3.1.1p2 */                                                         \
        RESERVED_WORD(TOKEN, DULCE  , u8"dulce"  )                             \
                                                                               \
        /* §3.1.1p3 */                                                         \
        TOKEN(                                                                 \
                END_STMT,                                                      \
                u8"terminador de frase",                                       \
                u8R"#((.))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.1.2p2 */                                                         \
        RESERVED_WORD(TOKEN, UN      , u8"un"      )                           \
                                                                               \
        /* §3.1.2p3 */                                                         \
        RESERVED_WORD(TOKEN, PLATO   , u8"plato"   )                           \
                                                                               \
        /* §3.1.2p4 */                                                         \
        RESERVED_WORD(TOKEN, SALSA   , u8"salsa"   )                           \
                                                                               \
        /* §3.1.2p2 */                                                         \
        RESERVED_WORD(TOKEN, HAY     , u8"salsa"   )                           \
                                                                               \
        /* §3.1.2p3 */                                                         \
        RESERVED_WORD(TOKEN, UN      , u8"salsa"   )                           \
                                                                               \
        /* §3.1.2p4 */                                                         \
        RESERVED_WORD(TOKEN, CUBIERTO, u8"cubierto")                           \
                                                                               \
        /* §3.1.2p5 */                                                         \
        RESERVED_WORD(TOKEN, PARA    , u8"para"    )                           \
                                                                               \
        /* §3.2.1p1 */                                                         \
        RESERVED_WORD(TOKEN, TAZAS   , u8"tazas"   )                           \
                                                                               \
        /* §3.2.2p1 */                                                         \
        TOKEN(                                                                 \
                BLOCK_OP,                                                      \
                u8"inicio de bloque",                                          \
                u8R"#((\{))#"                                                  \
        )                                                                      \
                                                                               \
        /* §3.2.2p2 */                                                         \
        TOKEN(                                                                 \
                BLOCK_CL,                                                      \
                u8"fin de bloque",                                             \
                u8R"#((\}))#"                                                  \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p1 */                                                       \
        TOKEN(                                                                 \
                TUPLE_OP,                                                      \
                u8"inicio de literal estructurado",                            \
                u8R"#((«))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p2 */                                                       \
        TOKEN(                                                                 \
                TUPLE_CL,                                                      \
                u8"fin de literal estructurado",                               \
                u8R"#((»))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p3 */                                                       \
        TOKEN(                                                                 \
                LABEL_ARROW,                                                   \
                u8"indicador de etiqueta",                                     \
                u8R"#((←))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.2p1 */                                                         \
        TOKEN(                                                                 \
                REF_MARK,                                                      \
                u8"indicador de referencia",                                   \
                u8R"#((&))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.1l1.1p1 */                                                   \
        TOKEN(                                                                 \
                OP_MINUS,                                                      \
                u8"operador de resta",                                         \
                u8R"#((−))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.2p1 */                                                   \
        TOKEN(                                                                 \
                OP_PLUS,                                                       \
                u8"operador de suma",                                          \
                u8R"#((\+))#"                                                  \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.3p1 */                                                   \
        TOKEN(                                                                 \
                OP_MULT,                                                       \
                u8"operador de multiplicación",                                \
                u8R"#((×))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.4p1 */                                                   \
        TOKEN(                                                                 \
                OP_DIV,                                                        \
                u8"operador de división",                                      \
                u8R"#((÷))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.4p1 */                                                   \
        TOKEN(                                                                 \
                OP_MOD,                                                        \
                u8"operador de módulo",                                        \
                u8R"#((~))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.5p1 */                                                   \
        TOKEN(                                                                 \
                OP_EQ,                                                         \
                u8"operador de igualdad",                                      \
                u8R"#((=))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.6p1 */                                                   \
        TOKEN(                                                                 \
                OP_NEQ,                                                        \
                u8"operador de no‐igualdad",                                   \
                u8R"#((≠))#"                                                   \
        )                                                                      \
                                                                               \
        /* §3.3.4p1 */                                                         \
        TOKEN(                                                                 \
                PAREN_OP,                                                      \
                u8"inicio de paréntesis",                                      \
                u8R"#((\())#"                                                  \
        )                                                                      \
                                                                               \
        /* §3.3.4p2 */                                                         \
        TOKEN(                                                                 \
                PAREN_CL,                                                      \
                u8"fin de paréntesis",                                         \
                u8R"#((\)))#"                                                  \
        )                                                                      \
                                                                               \
        /* §3.3.4p4 */                                                         \
        TOKEN(                                                                 \
                TUPLE_ARROW,                                                   \
                u8"indicador de acceso a arepa",                               \
                u8R"#((→))#"                                                   \
        )                                                                      \

#endif
