#include "Conf.h"

namespace basetool {
Conf::ConfData Conf::m_kvdata;

using std::stringstream;
using std::ifstream;
using std::string;

namespace detail {
void trim(string & str) {
    if (str.empty()) {
        return;
    }

    string::size_type begin = 0, end = 0;
    const char *s = str.c_str();

    while(*s++ == ' ') {
        ++begin;
    }
    s = str.c_str();

    end = str.size() - 1;
    while(end > begin && s[end] == ' ') {
        end--;
    }

    str = str.substr(begin, end - begin + 1);
}
}

int Conf::initConf(const string & pathfile) {
    ifstream fp(pathfile.c_str());
    if (!fp.is_open()) {
        fprintf(stderr, "Can't open config file:%s\n", pathfile.c_str());
        return -1;
    }

    string line, key, value;
    while (getline(fp, line)) {
        detail::trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        string::size_type pos = line.find('=');
        if (pos == string::npos) {
             continue;
        }

        key = line.substr(0, pos);
        value = line.substr(pos + 1);
        detail::trim(key);
        detail::trim(value);

        if (!key.empty() && !value.empty()) {
            m_kvdata[key] = value;
        }
    }

    fp.close();
    return 0;
}

string Conf::getString(const string & key, const std::string & def) {
    string ret;
    ConfData::iterator data = Conf::m_kvdata.find(key);
    if (data != m_kvdata.end() && !(data->second.empty())) {
        ret = data->second;
    } else {
        ret = def;
    }

    return ret;
}

int Conf::getInt(const std::string & key, const int def) {
    int ret = 0;
    ConfData::iterator data = m_kvdata.find(key);
    if (data != m_kvdata.end() && !(data->second.empty())) {
        ret = atoi(data->second.c_str());
    } else {
        ret = def;
    }

    return ret;
}

long long Conf::getInt64(const std::string & key, const long long def) {
    long long ret = 0;
    ConfData::iterator data = m_kvdata.find(key);
    if (data != m_kvdata.end() && !(data->second.empty())) {
        ret = atoll(data->second.c_str());
    } else {
        ret = def;
    }

    return ret;
}

float Conf::getFloat(const std::string & key, const float def) {
    float ret = 0;
    ConfData::iterator data = m_kvdata.find(key);
    if (data != m_kvdata.end() && !(data->second.empty())) {
        ret = atof(data->second.c_str());
    } else {
        ret = def;
    }

    return ret;
}

} // basetool

