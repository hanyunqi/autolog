/*
 * autolog/log_formatter.h
 *
 *  Created on: Sat Sep 19 10:50:43 2020
 *      Author: hanyunqi
 */

#ifndef AUTOLOG_LOG_FORMATTER_H_
#define AUTOLOG_LOG_FORMATTER_H_

#include <array>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

#include "autolog/common.h"
#include "autolog/log_session.h"

namespace AUTOLOG_NS {
class LogFormatter {
public:
    explicit LogFormatter(const std::string &tag) { Reset(tag); }
    LogFormatter() : delimiter_("||"), separator_("=") {}

    void Reset(const std::string &tag = AUTOLOG_TAG_DEFAULT) {
        ss_.str("");
        ss_ << std::fixed << std::setprecision(6);
        ss_ << tag;
        AddKV("traceid", LogSession::GetSession().GetTraceId());
        AddKV("spanid", LogSession::GetSession().GetSpanId());
    }

    inline void SetDelimiter(const std::string &delimiter) {
        delimiter_ = delimiter;
    }

    inline void SetSeparator(const std::string &separator) {
        separator_ = separator;
    }

    inline void AddDelimiter() { ss_ << delimiter_; }

    inline void AddKVSeparator() { ss_ << separator_; }

    template <class T>
    inline void Append(const T &v) {
        ss_ << v;
    }

    template <class T>
    inline void AppendV(const T &v, const std::string &start,
                        const std::string &end, const std::string &sep) {
        ss_ << start;
        for (auto iter = v.begin(); iter != v.end(); ++iter) {
            if (iter != v.begin()) ss_ << sep;
            Append(*iter);
        }
        ss_ << end;
    }

    template <class T>
    inline void AppendKV(const T &v, const std::string &start,
                         const std::string &end, const std::string &sep,
                         const std::string &kvsep) {
        ss_ << start;
        for (auto iter = v.begin(); iter != v.end(); iter++) {
            if (iter != v.begin()) ss_ << sep;
            ss_ << iter->first << kvsep << iter->second;
        }
        ss_ << end;
    }

    template <class T>
    inline void Append(const std::vector<T> &v, const std::string &sep = ", ") {
        AppendV(v, "[", "]", sep);
    }

    template <class T>
    inline void Append(const std::list<T> &v, const std::string &sep = ", ") {
        AppendV(v, "[", "]", sep);
    }

    template <class T>
    inline void Append(const std::set<T> &v, const std::string &sep = ", ") {
        AppendV(v, "[", "]", sep);
    }

    template <class T>
    inline void Append(const std::unordered_set<T> &v,
                       const std::string &sep = ", ") {
        AppendV(v, "[", "]", sep);
    }

    template <class T1, class T2>
    inline void Append(const std::map<T1, T2> &v, const std::string &sep = ", ",
                       const std::string &kvsep = ":") {
        AppendKV(v, "{", "}", sep, kvsep);
    }

    template <class T1, class T2>
    inline void Append(const std::unordered_map<T1, T2> &v,
                       const std::string &sep = ", ",
                       const std::string &kvsep = ":") {
        AppendKV(v, "{", "}", sep, kvsep);
    }

    template <class K, class V>
    inline void AddKV(const K &k, const V &v) {
        AddDelimiter();
        Append(k);
        AddKVSeparator();
        Append(v);
    }

    template <class K, class V, class... Types>
    inline void AddKV(const K &k, const V &v, const Types &... kvs) {
        AddKV(k, v);
        AddKV(kvs...);
    }

    std::string GetLogString() const { return ss_.str(); }
    void Clear() { ss_.str(""); }

private:
    std::string delimiter_;  // split key-value pairs
    std::string separator_;  // split key and value
    std::stringstream ss_;
};  // end of class LogFormatter

template <class K, class V, class... Types>
inline std::string AutoLogStr(const std::string &tag, const K &k, const V &v,
                              const Types &... kvs) {
    AUTOLOG_NS::LogFormatter formatter(tag);
    formatter.AddKV(k, v, kvs...);
    return formatter.GetLogString();
}
}  // end of namespace AUTOLOG_NS

#endif  // AUTOLOG_LOG_FORMATTER_H_
