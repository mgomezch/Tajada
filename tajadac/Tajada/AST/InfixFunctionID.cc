#include <string>

#include "Tajada/AST/Associativity.hh"
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/FunctionID.hh"
#include "Tajada/AST/InfixFunctionID.hh"

namespace Tajada {
        namespace AST {
                InfixFunctionID::InfixFunctionID(
                        std::string                * p_name         ,
                        std::string                * p_precedence   ,
                        Tajada::AST::Associativity   p_associativity
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::FunctionID(p_name),

                        precedence(std::stoi(*p_precedence)),
                        associativity(p_associativity)
                {}


                std::string InfixFunctionID::show(unsigned int depth) {
                        return
                                FunctionID::show(depth)
                                + std::string(u8" es infijo ")
                                + [associativity](){
                                        switch (associativity) {
                                                case Tajada::AST::Associativity::none : return u8""        ;
                                                case Tajada::AST::Associativity::left : return u8"zurdo "  ;
                                                case Tajada::AST::Associativity::right: return u8"diestro ";
                                        }
                                        return ""; // Just to silence a warning.
                                } ()
                                + std::to_string(precedence)
                        ;
                }
        }
}
