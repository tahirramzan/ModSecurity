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

#include "actions/transformations/md5.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include "modsecurity/transaction.h"
#include "actions/transformations/transformation.h"


namespace modsecurity {
namespace actions {
namespace transformations {

Md5::Md5(std::string action)
    : Transformation(action) {
    this->action_kind = 1;
}

std::string Md5::evaluate(std::string value,
    Transaction *transaction) {
    /**
     * @todo Implement the transformation Md5
     */
    if (transaction) {
#ifndef NO_LOGS
        transaction->debug(4, "Transformation Md5 is not implemented yet.");
#endif
    }
    return value;
}

}  // namespace transformations
}  // namespace actions
}  // namespace modsecurity
