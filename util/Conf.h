#ifndef CONF_H_
#define CONF_H_

#include <stdlib.h>

#include <map>
#include <string>
#include <fstream>
#include <sstream>

namespace basetool {
class Conf {
public:
    typedef std::map<std::string, std::string> ConfData;

    // success 0, error < 0
    // filter '#'
    static int initConf(const std::string & pathfile);

    static std::string getString(const std::string & key, const std::string & def = "");
    static int getInt(const std::string & key, const int def = 0);
    static long long getInt64(const std::string & key, const long long def = 0);
    static float getFloat(const std::string & key, const float def = 0.0);
private:
    static ConfData m_kvdata;

    Conf(const Conf&);
    void operator=(const Conf &);
};

}

#endif //CONF_H_
