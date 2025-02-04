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
#include <iostream>
#include <fstream>
#include <string>
#endif

#ifndef SRC_AUDIT_LOG_WRITER_SERIAL_H_
#define SRC_AUDIT_LOG_WRITER_SERIAL_H_

#include "audit_log/writer.h"
#include "modsecurity/transaction.h"

#ifdef __cplusplus

namespace modsecurity {
namespace audit_log {
namespace writer {

#define SERIAL_AUDIT_LOG_BOUNDARY_LENGTH 8

/** @ingroup ModSecurity_CPP_API */
class Serial : public audit_log::Writer {
 public:
    explicit Serial(audit_log::AuditLog *audit)
        : audit_log::Writer(audit) { }

    ~Serial() override;

    void refCountIncrease() override {
        m_refereceCount++;
    }


    void refCountDecreaseAndCheck() override {
        /*
        m_refereceCount--;


        if (m_refereceCount == 0) {
        */
        delete this;
        /*
        /}
        */
    }

    bool init() override;;
    bool write(Transaction *transaction, int parts) override;

 private:
    std::ofstream m_log;
    void generateBoundary(std::string *boundary);
};

}  // namespace writer
}  // namespace audit_log
}  // namespace modsecurity
#endif

#endif  // SRC_AUDIT_LOG_WRITER_SERIAL_H_
