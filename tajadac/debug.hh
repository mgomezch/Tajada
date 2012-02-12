/*
#define TAJADA_DEBUG_<module> 1

#if TAJADA_DEBUG_<module>
#       define TAJADA_DEBUG_<module>_PRINT(x) TAJADA_DEBUG_PRINT(<module>, x)
#       define TAJADA_DEBUG_<module>_DO(x) TAJADA_DEBUG_DO(<module>, x)
#else
#       define TAJADA_DEBUG_<module>_PRINT(x)
#       define TAJADA_DEBUG_<module>_DO(x)
#endif
*/

#define TAJADA_DEBUG_PRINT(module, x)      \
        do {                               \
                std::cerr                  \
                        << "TAJADA DEBUG " \
                        << #module         \
                        << " ("            \
                        << __FILE__        \
                        << ":"             \
                        << __LINE__        \
                        << "): "           \
                        << x               \
                        << std::endl;      \
        } while (0)

#define TAJADA_DEBUG_DO(module, x)         \
        do {                               \
                std::cerr                  \
                        << "TAJADA DEBUG " \
                        << #module         \
                        << " ("            \
                        << __FILE__        \
                        << ":"             \
                        << __LINE__        \
                        << "): ";          \
                x                          \
        } while (0)
