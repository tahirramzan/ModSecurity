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

#include "actions/transformations/base64_decode_ext.h"

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

Base64DecodeExt::Base64DecodeExt(std::string action)
    : Transformation(action) {
    this->action_kind = 1;
}

std::string Base64DecodeExt::evaluate(std::string value,
    Transaction *transaction) {
    /**
     * @todo Implement the transformation Base64DecodeExt
     */
    if (transaction) {
#ifndef NO_LOGS
        transaction->debug(4, "Transformation Base64DecodeExt is" \
            " not implemented yet.");
#endif
    }
    return value;
}

}  // namespace transformations
}  // namespace actions
}  // namespace modsecurity
