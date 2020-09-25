#include "../include/autolog/log_formatter.h"
#include "../include/autolog/buffered_log.h"

#include <iostream>

class BufferedLogFlusher {
 public:
  static void Flush(const std::string& log_str) {
    std::cout << "Flush: " << log_str << std::endl;
  }
};

void test_buffered_log() {
  autolog::BufferedLogFlushGuard<BufferedLogFlusher> guard("buffered_log");
  autolog::AppendLog(1, 2, "a", "b");
  autolog::AppendLog(3, 4, "a", "b");
  std::cout << autolog::BufferedLog::GetInstance().GetLogString() << std::endl;
}

int main() {
  autolog::LogSession::GetSession().Reset();
  autolog::LogFormatter lf;
  lf.Reset("_test");
  lf.AddKV(1, 2);
  std::vector<int> int_vec = {1, 2, 3};
  lf.AddKV(int_vec, int_vec);
  std::vector<std::map<int, int> > xx;
  xx.resize(2);
  xx[0][1] = 2;
  lf.AddKV("xx", xx);

  lf.AddKV(3, 4, "a", "b");
  std::cout << lf.GetLogString() << std::endl;

  test_buffered_log();
  return 0;
}
