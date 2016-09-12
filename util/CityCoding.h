// Author: Chen Ping 2016-09-29

#ifndef CITY_CODEING_H_
#define CITY_CODEING_H_

#include <stdlib.h>
#include <map>
#include <set>
#include <fstream>
#include <string>

// error code
// load
const int CODE_OK                   = 0 ;
const int CODE_OPEN_FILE_ERROR      = -1;
const int CODE_FILE_FORMAT_ERROR    = -2;

// isvalid
const int CODE_INVALID_PARAM        = -3;
const int CODE_DATA_IS_NULL         = -4;
const int CODE_INVALID_CODE         = -5;

typedef unsigned int uint32;
typedef int int32;

typedef struct load_data {
    uint32 province;
    uint32 city;
    uint32 district;
    uint32 code;
    std::string desc;
    load_data():province(0), city(0), district(0), code(0){}
}LOAD_DATA_S;

class CCityCode {
public:
    CCityCode():m_max_code(0), m_min_code(-1), m_pro_size(0), m_city_size(0), m_dist_size(0){}
    int load(const char * path);

    int isvalid(const std::string & code, std::string & desc);
    int isvalid(uint32 code, std::string & desc);
    int isvalid_province(uint32 code) {return m_province.find(code) == m_province.end();};
    int province_size() {return m_pro_size;};
    int city_size() {return m_city_size;};
    int district_size() {return m_dist_size;};
    int max_code() {return m_max_code;};
    int min_code() {return m_min_code;};
private:
    // No copying allowed
    CCityCode(const CCityCode &);
    void operator=(const CCityCode &);

    std::map<uint32, std::map<uint32, std::map<uint32, LOAD_DATA_S> > > m_load_data;
    std::set<uint32> m_province;
    uint32 m_max_code;
    int32 m_min_code;
    uint32 m_pro_size;
    uint32 m_city_size;
    uint32 m_dist_size;
};

#endif //CITY_CODEING_H_
