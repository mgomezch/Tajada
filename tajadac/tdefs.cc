#include "tokens.hh"

#define  TAJADA_TOKEN_BISON_DEFS(tag, description, regex, type) type|%token@<tag>@tag@description!
TAJADA_TOKEN_DATA(TAJADA_TOKEN_BISON_DEFS)
#undef TAJADA_TOKEN_BISON_DEFS
