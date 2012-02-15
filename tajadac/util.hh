#include <sstream>

// https://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string#comment-22
template <class T>
inline std::string to_string(T const & x) {
        std::stringstream ss;
        ss << x;
        return ss.str();
}
