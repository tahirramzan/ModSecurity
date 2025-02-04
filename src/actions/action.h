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
#include <iostream>

#include "modsecurity/intervention.h"
#include "modsecurity/rule.h"

#ifndef SRC_ACTIONS_ACTION_H_
#define SRC_ACTIONS_ACTION_H_

#ifdef __cplusplus

namespace modsecurity {
class Transaction;
class Rule;

namespace actions {


class Action {
 public:
    explicit Action(const std::string& _action)
        : action_kind(2),
        action(_action),
        name(_action),
        m_isNone(false),
        temporaryAction(false) {
            name.erase(0, 2);
        }
    explicit Action(const std::string& _action, int kind)
        : action_kind(kind),
        action(_action),
        name(_action),
        m_isNone(false),
        temporaryAction(false) {
            name.erase(0, 2);
        }

    virtual ~Action() { }
    /**
     *
     * Define the action kind regarding to the execution time.
     * 
     * 
     */
    enum Kind {
    /**
     *
     * Action that are executed while loading the configuration. For instance
     * the rule ID or the rule phase.
     *
     */
     ConfigurationKind,
    /**
     *
     * Those are actions that demands to be executed before call the operator.
     * For instance the tranformations.
     *
     *
     */
     RunTimeBeforeMatchAttemptKind,
    /**
     *
     * Actions that are executed after the execution of the operator, only if
     * the operator returned Match (or True). For instance the disruptive
     * actions.
     *
     */
     RunTimeOnlyIfMatchKind,
    };

    std::string action;
    int action_kind;
    std::string name;

    virtual std::string evaluate(std::string exp,
        Transaction *transaction);
    virtual bool evaluate(Rule *rule, Transaction *transaction);
    virtual bool evaluate(Rule *rule, Transaction *transaction,
        RuleMessage *ruleMessage) {
        return evaluate(rule, transaction);
    }
    virtual bool init(std::string *error) { return true; }
    virtual bool isDisruptive() { return false; }

    static Action *instantiate(const std::string& name);

    virtual void fill_intervention(ModSecurityIntervention *intervention);
    bool temporaryAction;
    bool m_isNone;
};


}  // namespace actions
}  // namespace modsecurity

#endif

#endif  // SRC_ACTIONS_ACTION_H_
