#include "tokens.hh"

#define TAJADA_TOKEN_BISON_TYPES(tag, description, regex, type) type|type@tag;!
TAJADA_TOKEN_DATA(TAJADA_TOKEN_BISON_TYPES)
#undef TAJADA_TOKEN_BISON_TYPES
