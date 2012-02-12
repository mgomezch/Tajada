#ifndef TAJADA_TOKENS_HH
#define TAJADA_TOKENS_HH

#define TAJADA_ENDLINES       "\u000A\u000B\u000C\u000D\u0085\u2028\u2029"
#define TAJADA_RESERVED_START u8"][←→()=≠~+÷×−&«»{}.,\\\\·‹⫽“\u0009-\u000D\u0020\u0085\u00A0\u1680\u180E\u2000-\u200A\u2028\u2029\u202F\u205F\u3000"

#define TAJADA_RESERVED_WORD(TOKEN, tag, word)                                          \
        TOKEN(                                                                          \
                tag,                                                                    \
                u8"palabra reservada “" word u8"”",                                     \
                u8"(" word u8")(?P<lookahead>[" TAJADA_RESERVED_START u8"]|$)",         \
                void                                                                    \
        )

#define TAJADA_TOKEN_DATA(TOKEN)                                               \
        /* §1.1p7 */                                                           \
        TOKEN(                                                                 \
                LIT_STR,                                                       \
                u8"literal de cadena de caracteres",                           \
                u8"(“(?:[^”\\\\]|\\\\.)*”)",                                   \
                std::string *                                                  \
        )                                                                      \
                                                                               \
        /* §1.2 */                                                             \
        TOKEN(                                                                 \
                IGNORE,                                                        \
                u8"espacio en blanco",                                         \
                u8"((?:"                                                       \
                        /* §1.2.1p4 (comentario de bloque) */                  \
                        u8"‹[^›]*›|"                                           \
                                                                               \
                        /* §1.2.2p4 (comentario de línea */                    \
                        u8"⫽[^" TAJADA_ENDLINES u8"]*"                         \
                        u8"["   TAJADA_ENDLINES u8"]|"                         \
                                                                               \
                        /* §1.2.2p5 (fin de línea) */                          \
                        u8"[" TAJADA_ENDLINES u8"]|"                           \
                                                                               \
                        /* §1.2.3p1 (espacio en blanco individual) */          \
                        /* Taken from the PropList.txt file in the Unicode  */ \
                        /* Character Database, version 6.0.0 (lines 11–22). */ \
                        u8"["                                                  \
                                u8"\u0009"                                     \
                                u8"\u0020"                                     \
                                u8"\u00A0"                                     \
                                u8"\u1680"                                     \
                                u8"\u180E"                                     \
                                u8"\u2000-\u200A"                              \
                                u8"\u202F"                                     \
                                u8"\u205F"                                     \
                                u8"\u3000"                                     \
                        u8"]"                                                  \
                u8")+)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §1.3.1p2 */                                                         \
        TOKEN(                                                                 \
                LIT_INT,                                                       \
                u8"literal entero",                                            \
                u8"([0-9]+)",                                                  \
                int                                                            \
        )                                                                      \
                                                                               \
        /* §1.3.2p1 */                                                         \
        TOKEN(                                                                 \
                FLOAT_SEP,                                                     \
                u8"separador de literal de punto flotante",                    \
                u8"(·)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §2.1.1p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, TETERO , u8"tetero" )                      \
                                                                               \
        /* §2.1.1p2 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, NEGRITO, u8"negrito")                      \
                                                                               \
        /* §2.1.1p3 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, CAFE   , u8"café"   )                      \
                                                                               \
        /* §2.1.2p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, CARAOTA, u8"caraota")                      \
                                                                               \
        /* §1.1p4, §2.1.2p3 */                                                 \
        TOKEN(                                                                 \
                LIT_CHR,                                                       \
                u8"literal de caraota",                                        \
                u8"(\\\\.)",                                                   \
                std::string *                                                  \
        )                                                                      \
                                                                               \
        /* §2.1.3p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, QUESO  , u8"queso"  )                      \
                                                                               \
        /* §2.1.4p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, PAPELON, u8"papelón")                      \
                                                                               \
        /* §2.2p3 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, AREPA  , u8"arepa"  )                      \
                                                                               \
        /* §2.2p4 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, VIUDA  , u8"viuda"  )                      \
                                                                               \
        /* §2.2p5 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, DE     , u8"de"     )                      \
                                                                               \
        /* §2.2p6 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, CON    , u8"con"    )                      \
                                                                               \
        /* §2.2p9 */                                                           \
        TOKEN(                                                                 \
                LIST_SEP,                                                      \
                u8"separador de lista",                                        \
                u8"(,)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §2.2p10 */                                                          \
        TAJADA_RESERVED_WORD(TOKEN, Y      , u8"y"      )                      \
                                                                               \
        /* §2.3p4 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, CACHAPA, u8"cachapa")                      \
                                                                               \
        /* §2.3p5 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, O      , u8"o"      )                      \
                                                                               \
        /* §2.4p2 */                                                           \
        TAJADA_RESERVED_WORD(TOKEN, ARROZ  , u8"arroz"  )                      \
                                                                               \
        /* §3.1.1p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, ES     , u8"es"     )                      \
                                                                               \
        /* §3.1.1p2 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, DULCE  , u8"dulce"  )                      \
                                                                               \
        /* §3.1.1p3 */                                                         \
        TOKEN(                                                                 \
                STMT_END,                                                      \
                u8"terminador de frase",                                       \
                u8"(\\.)",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.1.2p2 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, UN      , u8"un"      )                    \
                                                                               \
        /* §3.1.2p3 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, PLATO   , u8"plato"   )                    \
                                                                               \
        /* §3.1.2p4 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, SALSA   , u8"salsa"   )                    \
                                                                               \
        /* §3.1.2p2 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, HAY     , u8"hay"     )                    \
                                                                               \
        /* §3.1.2p3 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, CUBIERTO, u8"cubierto")                    \
                                                                               \
        /* §3.1.2p4 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, PARA    , u8"para"    )                    \
                                                                               \
        /* §3.2.1p1 */                                                         \
        TAJADA_RESERVED_WORD(TOKEN, TAZAS   , u8"tazas"   )                    \
                                                                               \
        /* §3.2.2p1 */                                                         \
        TOKEN(                                                                 \
                BLOCK_OP,                                                      \
                u8"inicio de bloque",                                          \
                u8"(\\{)",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.2.2p2 */                                                         \
        TOKEN(                                                                 \
                BLOCK_CL,                                                      \
                u8"fin de bloque",                                             \
                u8"(\\})",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p1 */                                                       \
        TOKEN(                                                                 \
                TUPLE_OP,                                                      \
                u8"inicio de literal estructurado",                            \
                u8"(«)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p2 */                                                       \
        TOKEN(                                                                 \
                TUPLE_CL,                                                      \
                u8"fin de literal estructurado",                               \
                u8"(»)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.1.2p3 */                                                       \
        TOKEN(                                                                 \
                LABEL_ARROW,                                                   \
                u8"indicador de etiqueta",                                     \
                u8"(←)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.2p1 */                                                         \
        TOKEN(                                                                 \
                REF_MARK,                                                      \
                u8"indicador de referencia",                                   \
                u8"(&)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.1l1.1p1 */                                                   \
        TOKEN(                                                                 \
                OP_MINUS,                                                      \
                u8"operador de resta",                                         \
                u8"(−)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.2p1 */                                                   \
        TOKEN(                                                                 \
                OP_PLUS,                                                       \
                u8"operador de suma",                                          \
                u8"(\\+)",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.3p1 */                                                   \
        TOKEN(                                                                 \
                OP_MULT,                                                       \
                u8"operador de multiplicación",                                \
                u8"(×)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.4p1 */                                                   \
        TOKEN(                                                                 \
                OP_DIV,                                                        \
                u8"operador de división",                                      \
                u8"(÷)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.4p1 */                                                   \
        TOKEN(                                                                 \
                OP_MOD,                                                        \
                u8"operador de módulo",                                        \
                u8"(~)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.5p1 */                                                   \
        TOKEN(                                                                 \
                OP_EQ,                                                         \
                u8"operador de igualdad",                                      \
                u8"(=)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.3.2l1.6p1 */                                                   \
        TOKEN(                                                                 \
                OP_NEQ,                                                        \
                u8"operador de no‐igualdad",                                   \
                u8"(≠)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.4p1 */                                                         \
        TOKEN(                                                                 \
                PAREN_OP,                                                      \
                u8"inicio de paréntesis",                                      \
                u8"(\\()",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.4p2 */                                                         \
        TOKEN(                                                                 \
                PAREN_CL,                                                      \
                u8"fin de paréntesis",                                         \
                u8"(\\))",                                                     \
                void                                                           \
        )                                                                      \
                                                                               \
        /* §3.3.4p4 */                                                         \
        TOKEN(                                                                 \
                TUPLE_ARROW,                                                   \
                u8"indicador de acceso a arepa",                               \
                u8"(→)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                ASSIGN,                                                        \
                u8"indicador de asignación",                                   \
                u8"(≔)",                                                       \
                void                                                           \
        )                                                                      \
                                                                               \
        /* TODO: sección */                                                    \
        TOKEN(                                                                 \
                IDENT,                                                         \
                u8"identificador",                                             \
                u8"([^" TAJADA_RESERVED_START "]+)",                           \
                void                                                           \
        )                                                                      \

#endif
