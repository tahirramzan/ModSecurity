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

#include "actions/deny.h"

#include <iostream>
#include <string>

#include "modsecurity/transaction.h"

namespace modsecurity {
namespace actions {

Deny::Deny(std::string action)
    : Action(action) {
    this->action = action;
    this->action_kind = 2;
}


bool Deny::evaluate(Rule *rule, Transaction *transaction) {
#ifndef NO_LOGS
    transaction->debug(8, "Running action deny");
#endif
    transaction->m_actions.push_back(this);
    return true;
}

void Deny::fill_intervention(ModSecurityIntervention *i) {
    if (i->status == 200) {
        i->status = 403;
    }
    i->log = "Deny action";
    i->disruptive = true;
}

}  // namespace actions
}  // namespace modsecurity
