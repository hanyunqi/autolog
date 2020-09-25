/*
 * autolog/log_session.h
 *
 *  Created on: Sat Sep 19 10:51:28 2020
 *      Author: hanyunqi
 */

#ifndef AUTOLOG_LOG_SESSION_H_
#define AUTOLOG_LOG_SESSION_H_

#include <sys/time.h>
#include <pthread.h>
#include <string>

namespace AUTOLOG_NS {
class LogSession {
public:
    LogSession() { spanid_[0] = '\0'; }

    static LogSession& GetSession() {
        static thread_local LogSession session;
        return session;
    }

    void Reset() {
        SetLogId("");
        SetTraceId("");
        SetSpanId();
    }

    void SetLogId(const std::string &logid) { logid_ = logid; }
    void SetTraceId(const std::string &traceid) { traceid_ = traceid; }
    void SetSpanId(const std::string &spanid) {
        snprintf(spanid_, SPANID_SIZE, "%s", spanid.c_str());
    }
    void SetSpanId() {
        timeval tv;
        gettimeofday(&tv, NULL);
        pthread_t threadId = pthread_self();
        long long int us = tv.tv_sec * 1000000 + tv.tv_usec;
        snprintf(spanid_, SPANID_SIZE, "%llu_%lld", (uint64_t)threadId, us);
    }
    void SetCSpanId(const std::string &cspanid) { cspanid_ = cspanid; }

    const std::string &GetLogId() { return logid_; }
    const std::string &GetTraceId() { return traceid_; }
    const char *GetSpanId() { return spanid_; }
    const std::string &GetCSpanId() { return cspanid_; }

    static const int SPANID_SIZE = 128;

private:
    std::string logid_;
    std::string traceid_;
    std::string cspanid_;
    char spanid_[SPANID_SIZE];
};  // end of class LogSession
}  // end of namespace AUTOLOG_NS
#endif  // AUTOLOG_LOG_SESSION_H_
