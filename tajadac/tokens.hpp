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
        /* §1.1 */                                                             \
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
        /* §1.3.2p1 */                                                         \
        TOKEN(                                                                 \
                LIT_FLOAT,                                                     \
                u8"literal de punto flotante",                                 \
                u8R"#(([0-9]+·[0-9]+))#"                                       \
        )                                                                      \
                                                                               \
        /* §1.3.1p2 */                                                         \
        TOKEN(                                                                 \
                LIT_INT,                                                       \
                u8"literal entero",                                            \
                u8R"#(([0-9]+))#"                                              \
        )                                                                      \
                                                                               \
        /* §2.1.1p1 */                                                         \
        RESERVED_WORD(TOKEN, BOOL , u8"café"   )                               \
        RESERVED_WORD(TOKEN, TRUE , u8"tetero" )                               \
        RESERVED_WORD(TOKEN, FALSE, u8"negrito")                               \
                                                                               \
        /* §2.1.2p1 */                                                         \
        RESERVED_WORD(TOKEN, CHAR , u8"caraota")                               \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                PAREN_OP,                                                      \
                u8"inicio de paréntesis",                                      \
                u8R"#((\())#"                                                  \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                PAREN_CL,                                                      \
                u8"fin de paréntesis",                                         \
                u8R"#((\)))#"                                                  \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                PLUS,                                                          \
                u8"operador de suma",                                          \
                u8R"#((\+))#"                                                  \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                MINUS,                                                         \
                u8"operador de resta",                                         \
                u8R"#((−))#"                                                   \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                MULT,                                                          \
                u8"operador de multiplicación",                                \
                u8R"#((×))#"                                                   \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                DIV,                                                           \
                u8"operador de división",                                      \
                u8R"#((÷))#"                                                   \
        )                                                                      \

#endif
