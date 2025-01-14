/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#include "variables/env.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <map>

#include "modsecurity/transaction.h"
#include "src/utils.h"

extern char **environ;

namespace modsecurity {
namespace Variables {

void Env::evaluateInternal(Transaction *transaction,
    std::vector<const transaction::Variable *> *l) {
    std::map<std::string, std::string> envs;
    for (char **current = environ; *current; current++) {
        std::string env = std::string(*current);
        size_t pos = env.find_first_of("=");
        if (pos == std::string::npos) {
            continue;
        }
        std::string key = std::string(env, 0, pos);
        std::string value = std::string(env, pos+1, env.length() - (pos + 1));

        envs.insert(std::pair<std::string, std::string>("ENV:" + key, value));
        if ("env:" + key == m_name) {
            l->push_back(new transaction::Variable(m_name, value));
            return;
        }
    }

    for (auto& x : envs) {
        if ((x.first.substr(0, m_name.size() + 1).compare(m_name + ":") != 0)
            && (x.first != m_name)) {
            continue;
        }
        l->push_back(new transaction::Variable(x.first, x.second));
    }
}


}  // namespace Variables
}  // namespace modsecurity
