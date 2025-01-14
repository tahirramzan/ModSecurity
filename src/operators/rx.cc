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

#include "operators/rx.h"

#include <string>
#include <list>

#include "operators/operator.h"
#include "src/macro_expansion.h"

namespace modsecurity {
namespace operators {



bool Rx::evaluate(Transaction *transaction, const std::string& input) {
    SMatch match;

    if (regex_search(input, &match, *m_re) && match.size() >= 1) {
        transaction->m_matched.push_back(match.match);
        return true;
    }

    return false;
}


}  // namespace operators
}  // namespace modsecurity
