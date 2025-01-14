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

#include "actions/rule_id.h"

#include <iostream>
#include <string>

#include "modsecurity/transaction.h"
#include "modsecurity/rule.h"

namespace modsecurity {
namespace actions {

bool RuleId::init(std::string *error) {
    std::string a = action;

    try {
        a.erase(0, 3);
        if (a.at(0) == '\'') {
            a.erase(0, 1);
            a.pop_back();
        }
        m_ruleId = std::stod(a);
    } catch (...) {
        m_ruleId = 0;
        error->assign("The input \"" + a + "\" does not " \
            "seems to be a valid rule id.");
        return false;
    }

    std::ostringstream oss;
    oss << std::setprecision(40) << m_ruleId;
    if (a != oss.str() || m_ruleId < 0) {
        error->assign("The input \"" + a + "\" does not seems " \
            "to be a valid rule id.");
        return false;
    }
    return true;
}

bool RuleId::evaluate(Rule *rule, Transaction *transaction) {
    rule->rule_id = m_ruleId;
    return true;
}

}  // namespace actions
}  // namespace modsecurity
