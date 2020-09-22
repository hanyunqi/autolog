/*
 * autolog/log_formatter.h
 *
 *  Created on: Sat Sep 19 10:50:43 2020
 *      Author: hanyunqi
 */

#ifndef AUTOLOG_LOG_FORMATTER_H_
#define AUTOLOG_LOG_FORMATTER_H_

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <string>
#include "autolog/common.h"

namespace AUTOLOG_NS {
class LogFormatter {
public:
    LogFormatter(const std::string &ltag) { Init(ltag); }
    LogFormatter() {}

    void Init(const std::string &ltag) {
        ss.str("");
        ss << std::fixed << std::setprecision(6);
        ss << ltag;
        AddKV("traceid", its::ng::LogSession::GetSession()->GetTraceId());
        AddKV("spanid", its::ng::LogSession::GetSession()->GetSpanId());
    }

    LogFormatter *AddKV(const char *k, const google::protobuf::Message &msg) {
        ss << "||" << k << "=" << msg.ShortDebugString();
        return this;
    }

    template <class K, class V>
    LogFormatter *AddKV(const K &k, const std::vector<V> &vs) {
        ss << "||" << k << "=";
        AddVec(vs);
        return this;
    }

    template <class K, class V>
    LogFormatter *AddKV(const K &k, const V &v) {
        ss << "||" << k << "=" << v;
        return this;
    }

    template <class T>
    LogFormatter *AddVec(const std::vector<T> &vs,
                         const std::string &sep = ", ") {
        ss << "[";
        for (size_t i = 0; i < vs.size(); i++) {
            if (i > 0) {
                ss << sep;
            }
            ss << vs[i];
        }
        ss << "]";
        return this;
    }

    template <class T>
    LogFormatter *AddVec(const std::list<T> &ls,
                         const std::string &sep = ", ") {
        ss << "[";
        auto iter = ls.begin();
        for (; iter != ls.end(); ++iter) {
            if (iter != ls.begin() {
                ss << sep;
            }
            ss << *iter;
        }
        ss << "]";
        return this;
    }

    template <class T>
    LogFormatter *AddVec(const std::vector<std::vector<T>> &vs,
                         const std::string &sep = ", ") {
        ss << "[";
        for (size_t i = 0; i < vs.size(); i++) {
            if (i > 0) {
                ss << sep;
            }
            AddVec(vs[i], sep);
        }
        ss << "]";
        return this;
    }

    template <class K, class V1, class V2>
    LogFormatter *AddKV(const K &k, const std::map<V1, V2> &vm) {
        ss << "||" << k << "={";
        for (auto iter = vm.begin(); iter != vm.end(); iter++) {
            if (iter != vm.begin()) {
                ss << ", ";
            }
            ss << iter->first << ":" << iter->second;
        }
        ss << "}";
        return this;
    }

    template <class K, class V1, class V2>
    LogFormatter *AddKV(const K &k, const std::unordered_map<V1, V2> &vm) {
        ss << "||" << k << "={";
        for (auto iter = vm.begin(); iter != vm.end(); iter++) {
            if (iter != vm.begin()) {
                ss << ", ";
            }
            ss << iter->first << ":" << iter->second;
        }
        ss << "}";
        return this;
    }

    template <class K, class V, class... Types>
    LogFormatter *AddKV(const K &k, const V &v, const Types &... kvs) {
        AddKV(k, v);
        AddKV(kvs...);
        return this;
    }

    std::string GetLogString() const { return ss.str(); }
    void Clear() { ss.str(""); }

private:
    std::stringstream ss;
};  // end of class LogFormatter

template <class K, class V, class... Types>
std::string AutoLogStr(const std::string &ltag, const K &k, const V &v,
                       const Types &... kvs) {
    AUTOLOG_NS::LogFormatter formatter(ltag);
    formatter.AddKV(k, v, kvs...);
    return formatter.GetLogString();
}
}  // end of namespace AUTOLOG_NS

#endif  // AUTOLOG_LOG_FORMATTER_H_
