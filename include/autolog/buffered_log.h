/*
 * autolog/buffered_log.h
 *
 *  Created on: Sat Sep 19 14:51:43 2020
 *      Author: hanyunqi
 */

#ifndef AUTOLOG_BUFFERED_LOG_H_
#define AUTOLOG_BUFFERED_LOG_H_

#include "autolog/log_formatter.h"

namespace AUTOLOG_NS {
class BufferedLog : public LogFormatter {
public:
    static BufferedLog& GetInstance() {
        static thread_local BufferedLog instance;
        return instance;
    }

    template <class K, class V, class... Types>
    inline void AppendLog(const K& k, const V& v, const Types&... kvs) {
        AddKV(k, v, kvs...);
    }
};  // end of class BufferedLog

template <class K, class V, class... Types>
inline void AppendLog(const K& k, const V& v, const Types&... kvs) {
    BufferedLog::GetInstance().AddKV(k, v, kvs...);
}

template <class Flusher>
class BufferedLogFlushGuard {
public:
    BufferedLogFlushGuard() {
        logger_ = &BufferedLog::GetInstance();
        logger_->Reset();
    }
    explicit BufferedLogFlushGuard(const std::string& tag) {
        logger_ = &BufferedLog::GetInstance();
        logger_->Reset(tag);
    }
    explicit BufferedLogFlushGuard(BufferedLog& logger) : logger_(&logger) {}
    ~BufferedLogFlushGuard() {
        if (logger_) {
            Flusher::Flush(logger_->GetLogString());
            logger_->Clear();
            logger_ = NULL;
        }
    }

private:
    BufferedLog* logger_;
};  // end of class BufferedLogFlushGuard
}  // end of namespace AUTOLOG_NS

#endif  // AUTOLOG_BUFFERED_LOG_H_
