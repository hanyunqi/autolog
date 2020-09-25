/*
 * autolog/writer_log4cplus.h
 *
 *  Created on: Sat Sep 19 11:14:57 2020
 *      Author: hanyunqi
 */

#ifndef AUTOLOG_WRITER_LOG4CPLUS_H_
#define AUTOLOG_WRITER_LOG4CPLUS_H_
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

namespace AUTOLOG_NS {

#ifndef AUTOLOG_DEBUG_TAG
#define AUTOLOG_DEBUG_TAG "root"
#endif

#ifndef AUTOLOG_TRACE_TAG
#define AUTOLOG_TRACE_TAG AUTOLOG_DEBUG_TAG
#endif

#ifndef AUTOLOG_INFO_TAG
#define AUTOLOG_INFO_TAG AUTOLOG_TRACE_TAG
#endif

#ifndef AUTOLOG_WARN_TAG
#define AUTOLOG_WARN_TAG AUTOLOG_INFO_TAG
#endif

#ifndef AUTOLOG_ERROR_TAG
#define AUTOLOG_ERROR_TAG AUTOLOG_WARN_TAG
#endif

#ifndef AUTOLOG_FATAL_TAG
#define AUTOLOG_FATAL_TAG AUTOLOG_ERROR_TAG
#endif

// DEBUG
#ifndef AUTOLOG_DISABLE_DEBUG
static log4cplus::Logger logger_debug =
    log4cplus::Logger::getInstance(std::string(AUTOLOG_DEBUG_TAG));

#define ADEBUG_STR_LOG(event) LOG4CPLUS_DEBUG_STR(logger_debug, event)
#define ADEBUG_FMT_LOG(fmt, ...) \
    LOG4CPLUS_DEBUG_FMT(logger_debug, fmt, ##__VA_ARGS__)

#define ADEBUG_LOG(tag, key, value, ...) \
    DEBUG_STR_LOG(AutoLogStr(tag, key, value, ##__VA_ARGS__))

#define ADEBUG_KV_LOG(key, value, ...) \
    ADEBUG_LOG(AUTOLOG_TAG_DEFAULT, key, value, ##__VA_ARGS__)
#else
#define ADEBUG_STR_LOG(event) ((void)0)
#define ADEBUG_FMT_LOG(fmt, ...) ((void)0)
#define ADEBUG_LOG(tag, key, value, ...) ((void)0)
#define ADEBUG_KV_LOG(key, value, ...) ((void)0)
#endif

// TRACE
// INFO
// WARNING
// ERROR
// FATAL

}  // end of namespace AUTOLOG_NS

#endif  // AUTOLOG_WRITER_LOG4CPLUS_H_
