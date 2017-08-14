#include "CityCoding.h"

using std::string;
using std::map;

namespace detail {
bool is_digits(const string & str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void str_trim(string & str) {
    string::size_type begin = 0, end = 0;
    const char *s = str.c_str();

    while(*s++ == ' ') {
        ++begin;
    }
    s = str.c_str();

    end = str.size() - 1;
    while(end > begin && (s[end] == ' ' || s[end] == '\r')) {
        end--;
    }

    str = str.substr(begin, end - begin + 1);
}

void code_parse(const uint32 & code, uint32 & province,
        uint32 & city, uint32 & district){
    district = code % 100;
    city = code / 100 % 100;
    province = code / 10000;
}
}


int CCityCode::load(const char * path) {
    std::ifstream file;

    file.open(path);
    if (!file.good()) {
        return CODE_OPEN_FILE_ERROR;
    }

    uint32 last_pro = 0, last_city = 0, last_dist = 0;
    string last_pro_desc, last_city_desc, last_dist_desc;
    string line;
    while(getline(file, line)) {
        //pase line
        string::size_type space_pos = line.find(" ");
        if (space_pos == string::npos) {
            file.close();
            return CODE_FILE_FORMAT_ERROR;
        }

        string code = line.substr(0, space_pos);
        string code_desc = line.substr(space_pos + 1);
        detail::str_trim(code);
        detail::str_trim(code_desc);

        if (code.empty() || code_desc.empty()) {
            file.close();
            return CODE_FILE_FORMAT_ERROR;
        }

        //pase code
        uint32 pro = 99, city = 99, dist = 99;
        uint32 c = atoi(code.c_str());
        if (c == 0) {
            file.close();
            return CODE_INVALID_CODE;
        }

        detail::code_parse(c, pro, city, dist);
        if (pro != last_pro) {
            last_pro = pro;
            last_city = city;
            last_dist = dist;
            last_pro_desc = code_desc;
            last_city_desc = "";
            last_dist_desc = "";
        } else if (city != last_city) {
            last_city = city;
            last_dist = dist;
            last_city_desc = code_desc;
            last_dist_desc = "";
        } else if (dist != last_dist) {
            last_dist = dist;
            last_dist_desc = code_desc;
        }

        // update max and min code
        if (c > m_max_code) {
             m_max_code = c;
        }

        if (c < m_min_code) {
            m_min_code = c;
        }

        // update size
        if (pro != 0 && city == 0 && dist == 0) {
             m_pro_size++;
             m_province.insert(c);
        }

        if (pro != 0 && city != 0 && dist == 0) {
             m_city_size++;
        }

        if (pro != 0 && city != 0 && dist != 0) {
             m_dist_size++;
        }

        LOAD_DATA_S d;
        d.province = pro;
        d.city = city;
        d.district = dist;
        d.code = c;
        d.desc = last_pro_desc + "--" + last_city_desc + "--" + last_dist_desc;
        m_load_data[pro][city][dist] = d;
    }


    file.close();
    return CODE_OK;
}

int CCityCode::isvalid(const string & c, string & desc) {
    string code = c;
    detail::str_trim(code);
    if (code.empty() || !detail::is_digits(code)){
         return CODE_INVALID_PARAM;
    }
    return isvalid(atoi(code.c_str()), desc);
}

int CCityCode::isvalid(uint32 code, string & desc) {
    if (code == 0 || code < 110000 || code > 820000) {
        return CODE_INVALID_PARAM;
    }

    if (m_load_data.empty()) {
         return CODE_DATA_IS_NULL;
    }

    uint32 pro = 0, city = 0, dist = 0;
    detail::code_parse(code, pro, city, dist);

    LOAD_DATA_S * d = NULL;
    map<uint32, map<uint32, map<uint32, LOAD_DATA_S> > >::iterator it_pro;
    if ((it_pro = m_load_data.find(pro)) != m_load_data.end()) {
        map<uint32, map<uint32, LOAD_DATA_S> >::iterator it_city;
        if ((it_city = it_pro->second.find(city)) != it_pro->second.end()) {
            map<uint32, LOAD_DATA_S>::iterator data;
            if ((data = it_city->second.find(dist)) != it_city->second.end()) {
                d = &(data->second);
            }
        }
    }

    if (d != NULL) { // not find
        desc = d->desc;
    }

    return d == NULL ? CODE_INVALID_CODE : CODE_OK;
}

