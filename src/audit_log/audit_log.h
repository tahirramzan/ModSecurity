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

#ifndef SRC_AUDIT_LOG_AUDIT_LOG_H_
#define SRC_AUDIT_LOG_AUDIT_LOG_H_

#include "modsecurity/transaction.h"
#include "audit_log/writer.h"

#ifdef __cplusplus

namespace modsecurity {
namespace audit_log {

/** @ingroup ModSecurity_CPP_API */
class AuditLog {
 public:
    AuditLog();
    ~AuditLog();

    void refCountIncrease();
    void refCountDecreaseAndCheck();

    enum AuditLogType {
     SerialAuditLogType,
     ParallelAuditLogType,
    };

    enum AuditLogStatus {
     OnAuditLogStatus,
     OffAuditLogStatus,
     RelevantOnlyAuditLogStatus
    };

    enum AuditLogParts {
     /**
      * Audit log header (mandatory).
      * 
      */
     AAuditLogPart = 2,

     /**
      * Request headers.
      * 
      */
     BAuditLogPart = 4,

     /**
      * Request body (present only if the request body exists and ModSecurity
      * is configured to intercept it).
      * 
      */     
     CAuditLogPart = 8,

     /**
      * Reserved for intermediary response headers; not implemented yet.
      * 
      */     
     DAuditLogPart = 16,

     /**
      * Intermediary response body (present only if ModSecurity is configured
      * to intercept response bodies, and if the audit log engine is
      * configured to record it). Intermediary response body is the same as the
      * actual response body unless ModSecurity intercepts the intermediary
      * response body, in which case the actual response body will contain the
      * error message (either the Apache default error message, or the
      * ErrorDocument page).
      *
      */
     EAuditLogPart = 32,

     /**
      * Final response headers (excluding the Date and Server headers, which
      * are always added by Apache in the late stage of content delivery).
      * 
      */
     FAuditLogPart = 64,

     /**
      * Reserved for the actual response body; not implemented yet.
      * 
      */
     GAuditLogPart = 128,

     /**
      * Audit log trailer.
      * 
      */
     HAuditLogPart = 256,

     /**
      * This part is a replacement for part C. It will log the same data as C
      * in all cases except when multipart/form-data encoding in used. In this
      * case, it will log a fake application/x-www-form-urlencoded body that
      * contains the information about parameters but not about the files. This
      * is handy if you don’t want to have (often large) files stored in your
      * audit logs.
      * 
      */
     IAuditLogPart = 512,

     /**
      * This part contains information about the files uploaded using
      * multipart/form-data encoding.
      */
     JAuditLogPart = 1024,

     /**
      * This part contains a full list of every rule that matched (one per
      * line) in the order they were matched. The rules are fully qualified and
      * will thus show inherited actions and default operators. Supported as of
      * v2.5.0.
      * 
      */
     KAuditLogPart = 2048,

     /**
      * Final boundary, signifies the end of the entry (mandatory).
      * 
      */
     ZAuditLogPart = 4096
    };

    bool setStorageDirMode(int permission);
    bool setFileMode(int permission);
    bool setStatus(AuditLogStatus new_status);
    bool setRelevantStatus(const std::basic_string<char>& new_relevant_status);
    bool setFilePath1(const std::basic_string<char>& path);
    bool setFilePath2(const std::basic_string<char>& path);
    bool setStorageDir(const std::basic_string<char>& path);

    bool setParts(const std::basic_string<char>& new_parts);
    bool setType(AuditLogType audit_type);

    bool init();
    bool close();

    bool saveIfRelevant(Transaction *transaction);
    bool saveIfRelevant(Transaction *transaction, int parts);
    bool isRelevant(int status);

    int addParts(int parts, const std::string& new_parts);
    int removeParts(int parts, const std::string& new_parts);

    std::string m_path1;
    std::string m_path2;
    std::string m_storage_dir;

    int filePermission;
    int directoryPermission;

    int m_parts;

 private:
    AuditLogStatus m_status;


    AuditLogType m_type;
    std::string m_relevant;

    audit_log::Writer *m_writer;
    int m_refereceCount;
};

}  // namespace audit_log
}  // namespace modsecurity
#endif

#endif  // SRC_AUDIT_LOG_AUDIT_LOG_H_
