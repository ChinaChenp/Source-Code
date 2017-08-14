// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

/// modify from Leveldb by @author  chen ping

#include "TestFramework.h"

#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace leveldb {

namespace {
    struct Test {
        const char* base;
        const char* name;
        void (*func)();
    };
    std::vector<Test>* tests;
}

bool RegisterTest(const char* base, const char* name, void (*func)()) {
    if (tests == NULL) {
        tests = new std::vector<Test>;
    }
    Test t;
    t.base = base;
    t.name = name;
    t.func = func;
    tests->push_back(t);
    return true;
}

int RunAllTests() {
    const char* matcher = getenv("LEVELDB_TESTS");

    int num = 0;
    if (tests != NULL) {
        for (size_t i = 0; i < tests->size(); i++) {
            const Test& t = (*tests)[i];
            if (matcher != NULL) {
                std::string name = t.base;
                name.push_back('.');
                name.append(t.name);
                if (strstr(name.c_str(), matcher) == NULL) {
                    continue;
                }
            }

            leveldb::Timer times;
            fprintf(stderr, "\033[40;32m==== Test\033[0m %s.%s ", t.base, t.name);
            (*t.func)();
            fprintf(stderr, "(%.2f ms)\n", times.elapse());
            ++num;
        }
    }
    fprintf(stderr, "\033[40;32m==== PASSED %d tests\033[0m\n", num);
    return 0;
}
}  // namespace leveldb
