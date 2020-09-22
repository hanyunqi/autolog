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

    void Flush() {}
};  // end of class BufferedLog

template<class Flusher>
class BufferedLogFlushGuard {
public:
    explicit BufferedLogFlushGuard(BufferedLog& logger) : logger_(&logger) {}
    ~BufferedLogFlushGuard() {
        if (logger_) {
            Flusher::Flush(logger_->GetLogString());
            logger_->Clear();
        }
    }

private:
    BufferedLog* logger_;
};  // end of class BufferedLogFlushGuard
}  // end of namespace AUTOLOG_NS

#endif  // AUTOLOG_BUFFERED_LOG_H_
