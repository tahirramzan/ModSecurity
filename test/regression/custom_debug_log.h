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

#include <sstream>
#include <string>

#include "modsecurity/debug_log.h"

#ifndef TEST_REGRESSION_CUSTOM_DEBUG_LOG_H_
#define TEST_REGRESSION_CUSTOM_DEBUG_LOG_H_

namespace modsecurity_test {

class CustomDebugLog : public modsecurity::DebugLog {
 public:
    CustomDebugLog *new_instance();

    void write(int level, const std::string& message) override;
    bool contains(const std::string& pattern);
    std::string log_messages();

 private:
    std::stringstream m_log;
};

}  // namespace modsecurity_test

#endif  // TEST_REGRESSION_CUSTOM_DEBUG_LOG_H_
