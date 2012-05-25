#include <string>

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/FunctionID.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                FunctionDeclaration::FunctionDeclaration(
                        Tajada::AST::FunctionID * p_id         ,
                        std::string             * p_domain_name,
                        Tajada::Type::Type      * p_domain     ,
                        Tajada::Type::Type      * p_codomain
                ):
                        id         (p_id         ),
                        domain_name(p_domain_name),
                        domain     (p_domain     ),
                        codomain   (p_codomain   )
                {}


                std::string FunctionDeclaration::show(unsigned int depth) {
                        return
                                id->show()
                                + std::string(u8" de ")
                                + domain->show(depth)
                                + u8" "
                                + *domain_name
                                + std::string(u8" y salsa de ")
                                + codomain->show(depth)
                        ;
                }
        }
}
