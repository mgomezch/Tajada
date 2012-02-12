#include "tokens.hh"

#define  TAJADA_TOKEN_BISON_DEFS(tag, description, regex, type) TOKEN type|%token <tag> tag !
TAJADA_TOKEN_DATA(TAJADA_TOKEN_BISON_DEFS)
#undef TAJADA_TOKEN_BISON_DEFS

%union {
#define TAJADA_TOKEN_BISON_TYPES(tag, description, regex, type) UNION type|type tag; !
TAJADA_TOKEN_DATA(TAJADA_TOKEN_BISON_TYPES)
#undef TAJADA_TOKEN_BISON_TYPES
}
