#ifndef BASE_TOOL_URLCODEC_H_
#define BASE_TOOL_URLCODEC_H_

#include <string>

namespace basetool {

    std::string UrlDecode(const std::string & url);
    std::string UrlEncode(const std::string & url);
}
#endif //BASE_TOOL_URLCODEC_H_
