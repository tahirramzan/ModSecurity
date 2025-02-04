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

#include "actions/transformations/trim_right.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include "modsecurity/transaction.h"
#include "actions/transformations/transformation.h"
#include "actions/action.h"

namespace modsecurity {
namespace actions {
namespace transformations {


TrimRight::TrimRight(std::string action)
    : Trim(action) {
    this->action_kind = 1;
}

std::string TrimRight::evaluate(std::string value,
    Transaction *transaction) {
    return *this->rtrim(&value);
}

}  // namespace transformations
}  // namespace actions
}  // namespace modsecurity
