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

/** @file modsecurity.h Main ModSecurity header file */

/** @mainpage ModSecurity - open source, cross platform web application firewall
 *
 * Example Usage:
 * @code
 *
 * using ModSecurity::ModSecurity;
 * using ModSecurity::Rules;
 * using ModSecurity::Transaction;
 *
 * ModSecurity *modsec;
 * ModSecurity::Rules *rules;
 *
 * modsec = new ModSecurity();
 * rules = new Rules();
 * rules->loadFromUri(rules_file);
 *
 * Transaction *modsecTransaction = new Transaction(modsec, rules);
 * modsecTransaction->processConnection("127.0.0.1");
 *
 * if (modsecTransaction->intervention()) {
 *     std::cout << "There is an intervention" << std::endl;
 * }
 *
 * ...      
 *
 * @endcode
 * 
 */

/**
 * @defgroup ModSecurity_C_API ModSecurity C API
 *
 * This is the ModSecurity C API description
 *
 * At this page you can get information on how the extend your C
 * application, by embedding ModSecurity.
 *
 */


/**
 * @defgroup ModSecurity_CPP_API ModSecurity CPP API
 *
 * This is the ModSecurity CPP API description.
 *
 * At this page you can get information on how the extend your CPP
 * application, by embedding ModSecurity.
 *
 */


/**
 * @defgroup ModSecurity_Operator ModSecurity Operators
 *
 * SecLanguage operator
 */


#ifdef __cplusplus
#include <ctime>
#include <iostream>
#include <string>
#endif


#ifndef HEADERS_MODSECURITY_MODSECURITY_H_
#define HEADERS_MODSECURITY_MODSECURITY_H_


#ifndef __cplusplus
typedef struct ModSecurity_t modsecurity;
#endif


#include "modsecurity/intervention.h"
#include "modsecurity/transaction.h"
#include "modsecurity/debug_log.h"
#include "modsecurity/rules.h"

/**
 * TAG_NUM:
 *
 * Alpha  - 001
 * Beta   - 002
 * Dev    - 010
 * Rc1    - 051
 * Rc2    - 052
 * ...    - ...
 * Release- 100
 *
 */

#define MODSECURITY_MAJOR "3"
#define MODSECURITY_MINOR "0"
#define MODSECURITY_PATCHLEVEL "0"
#define MODSECURITY_TAG "-alpha"
#define MODSECURITY_TAG_NUM "001"

#define MODSECURITY_VERSION MODSECURITY_MAJOR "." \
    MODSECURITY_MINOR "." MODSECURITY_PATCHLEVEL \
    MODSECURITY_TAG

#define MODSECURITY_VERSION_NUM MODSECURITY_MAJOR \
    MODSECURITY_MINOR MODSECURITY_PATCHLEVEL MODSECURITY_TAG_NUM

typedef void (*LogCb) (void *, const char *);

#ifdef __cplusplus
namespace modsecurity {

/* few forwarded declarations */
namespace actions {
class Action;
}
namespace operators {
class Operators;
}
class Rule;

/** @ingroup ModSecurity_CPP_API */
class ModSecurity {
 public:
    ModSecurity();
    ~ModSecurity();

    static const std::string whoAmI();
    void setConnectorInformation(std::string connector);
    void setServerLogCb(LogCb cb);
    void serverLog(void *data, const std::string& msg);
    const std::string& getConnectorInformation();

    /**
     *
     * The Phases enumerator consists in mapping the different stages of a
     * given request. ModSecurity is expected to inspect data based on those
     * "phases". If your module/application use this in a different order, it
     * will lead ModSecurity to act in an unexpected behavior.
     *
     * It is mandatory to call all the phases, even if you don't have this
     * phases segmented in your end.
     *
     */
    enum Phases {
    /**
     *
     * The connection is the very first information that ModSecurity can
     * inspect. It is expected to happens before the virtual host name be
     * resolved. This phase is expected to happen immediately after a
     * connection is established.
     *
     */
     ConnectionPhase,
    /**
     *
     * The "URI" phase happens just after the web server (or any other
     * application that you may use with ModSecurity) have the acknowledgement
     * of the full request URI.
     *
     */
     UriPhase,
    /**
     *
     * The "RequestHeaders" phase happens when the server has all the
     * information about the headers. Notice however, that it is expected to
     * happen prior to the reception of the request body (if any).
     *
     */
     RequestHeadersPhase,
    /**
     *
     * At the "RequestHeaders" phase, ModSecurity is expected to inspect the
     * content of a request body, that does not happens when the server has all
     * the content but prior to that, when the body transmission started.
     * ModSecurity can ask the webserver to block (or make any other disruptive
     * action) while the client is still transmitting the data.
     *
     */
     RequestBodyPhase,
    /**
     *
     * The "ResponseHeaders" happens just before all the response headers are
     * ready to be delivery to the client.
     *
     */
     ResponseHeadersPhase,
    /**
     *
     * Same as "RequestBody" the "ResponseBody" phase perform a stream
     * inspection which may result in a disruptive action.
     *
     */
     ResponseBodyPhase,
    /**
     *
     * The last phase is the logging phase. At this phase ModSecurity will
     * generate the internal logs, there is no need to hold the request at
     * this point as this phase does not produce any kind of action.
     *
     */
     LoggingPhase,
    /**
     * Just a marking for the expected number of phases.
     * 
     */
     NUMBER_OF_PHASES,
    };

 private:
    std::string m_connector;
    LogCb m_logCb;
};


#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup ModSecurity_C_API */
ModSecurity *msc_init();
/** @ingroup ModSecurity_C_API */
const char *msc_who_am_i(ModSecurity *msc);
/** @ingroup ModSecurity_C_API */
void msc_set_connector_info(ModSecurity *msc, const char *connector);
/** @ingroup ModSecurity_C_API */
void msc_set_log_cb(ModSecurity *msc, LogCb cb);
/** @ingroup ModSecurity_C_API */
void msc_cleanup(ModSecurity *msc);

#ifdef __cplusplus
}


}  // namespace modsecurity
#endif

#endif  // HEADERS_MODSECURITY_MODSECURITY_H_
