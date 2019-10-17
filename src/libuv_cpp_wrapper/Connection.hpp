#ifndef _CONNECTION123_HPP_
#define _CONNECTION123_HPP_
#include "uv.h"
#include <memory>
#include "Handle.hpp"
#include <functional>
#include <string>

namespace uvx {
class Connection;
using ReadFunc_t = std::function<void(Connection*)>;
// using Alloc_t = std::function<void (uv_handle_t*, size_t, uv_buf_t* buf)>;
using WriteFunc_t = std::function<void()>;
class Tcp;

class Connection : public Handle, public std::enable_shared_from_this<Connection>{
public:
  // using Handle::Handle;
  Connection(uv_tcp_t* handle, Tcp* tcp);
  void startRead();
  void write(const char* str, int len);
  const uv_buf_t* getBuf();
  uv_write_t* getReq();
  uv_tcp_t* getHandle();

  ssize_t remain = INT_MIN; //  remain len to read
  void close_cb() override;
  std::string reserve_for_read = "";
  ReadFunc_t readFunc;
  WriteFunc_t wfunc;
private:
  Tcp* tcp;
  uv_write_t req;
  uv_buf_t buf;
  std::string reserve; // reserve for buf 
  std::shared_ptr<Connection> sharedMe();
  
  void setReserve(const char *, size_t);
  static uv_alloc_cb allocFunc;
};
}

#endif //CONNECTION_HPP_