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


#ifdef __cplusplus
#include <string>
#endif


#ifndef HEADERS_MODSECURITY_TRANSACTION_VARIABLE_H_
#define HEADERS_MODSECURITY_TRANSACTION_VARIABLE_H_


#ifndef __cplusplus
typedef struct Variable_t Variable;
#endif

#ifdef __cplusplus
namespace modsecurity {
namespace transaction {

class Variable {
 public:
     Variable(const std::string& key, const std::string& value) :
        m_key(key),
        m_value(value) { }
     std::string m_key;
     std::string m_value;
};

}  // namespace transaction
}  // namespace modsecurity
#endif

#endif  // HEADERS_MODSECURITY_TRANSACTION_VARIABLE_H_
