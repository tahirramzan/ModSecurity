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

#include "actions/log.h"

#include <iostream>
#include <string>

#include "modsecurity/transaction.h"

namespace modsecurity {
namespace actions {

bool Log::evaluate(Rule *rule, Transaction *transaction) {
    transaction->m_toBeSavedInAuditlogs = true;
    /* FIXME: transaction->serverLog("Something...."); */
    transaction->debug(9, "Saving transaction to logs");
    return true;
}

}  // namespace actions
}  // namespace modsecurity
