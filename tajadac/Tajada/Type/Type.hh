#ifndef TAJADA_TYPE_TYPE_HH
#define TAJADA_TYPE_TYPE_HH

#include <string>

namespace Tajada {
        namespace Type {
                class Type {
                        public:
                                enum class Complete : bool {
                                        incomplete,
                                        complete
                                } is_complete;

                                Type(
                                        Complete p_is_complete
                                );

                                virtual unsigned int size();
                                virtual unsigned int alignment();

                                virtual std::string show(unsigned int depth = 0) = 0;

                                virtual ~Type() = 0;

                        protected:
                                bool has_saved_size;
                                unsigned int saved_size;

                                bool has_saved_alignment;
                                unsigned int saved_alignment;

                                virtual unsigned int size_()      = 0;
                                virtual unsigned int alignment_() = 0;
                };

                bool operator == (Tajada::Type::Type const &, Tajada::Type::Type const &);
                bool operator != (Tajada::Type::Type const &, Tajada::Type::Type const &);
        }
}

#endif
