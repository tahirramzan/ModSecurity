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

#include <string>

#include "actions/action.h"

#ifndef SRC_ACTIONS_SET_VAR_H_
#define SRC_ACTIONS_SET_VAR_H_

namespace modsecurity {
class Transaction;
class Rule;

namespace actions {


class SetVar : public Action {
 public:
    explicit SetVar(std::string action);

    bool evaluate(Rule *rule, Transaction *transaction) override;
    void dump();
    bool init(std::string *error) override;

    std::string collectionName;
    std::string variableName;
    std::string predicate;

    enum SetVarOperation {
        /* Set variable to something */
        setOperation,
        /* read variable, sum predicate and set */
        sumAndSetOperation,
        /* read variable, substract predicate and set */
        substractAndSetOperation,
        /* set variable to 1 */
        setToOne
    };

    SetVarOperation operation;
};

}  // namespace actions
}  // namespace modsecurity


#endif  // SRC_ACTIONS_SET_VAR_H_
