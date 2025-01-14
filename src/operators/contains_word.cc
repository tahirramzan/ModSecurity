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

#include "operators/contains_word.h"

#include <string>

#include "operators/operator.h"
#include "src/macro_expansion.h"

namespace modsecurity {
namespace operators {

bool ContainsWord::acceptableChar(const std::string& a, size_t pos) {
    if (a.size() - 1 < pos) {
        return false;
    }

    if ((a.at(pos) >= 65 && a.at(pos) <= 90) ||
        (a.at(pos) >= 97 && a.at(pos) <= 122)) {
        return false;
    }

    return true;
}

bool ContainsWord::evaluate(Transaction *transaction,
    const std::string& input) {
    std::string paramTarget = MacroExpansion::expand(param, transaction);

    if (paramTarget.empty()) {
        return true;
    }
    if (input.empty()) {
        return false;
    }
    if (input == paramTarget) {
        return true;
    }

    size_t pos = input.find(paramTarget);
    while (pos != std::string::npos) {
        if (pos == 0 && acceptableChar(input, paramTarget.size())) {
            return true;
        }
        if (pos + paramTarget.size() == input.size() &&
            acceptableChar(input, pos - 1)) {
            return true;
        }
        if (acceptableChar(input, pos - 1) &&
            acceptableChar(input, pos + paramTarget.size())) {
            return true;
        }
        pos = input.find(paramTarget, pos + 1);
    }

    return false;
}


}  // namespace operators
}  // namespace modsecurity
