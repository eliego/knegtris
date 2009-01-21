#ifndef __EXCEPTION
#define __EXCEPTION
#include <string>

class Exception {
public:
  Exception(std::string mess) : m_mess(mess) {}
  std::string getMess() { return m_mess; }
  
private:
  std::string m_mess;
};

class InvalidValues : public Exception {
public:
  InvalidValues(std::string mess) : Exception(mess) {}
};

class InvalidPosition : public Exception {
public:
  InvalidPosition(std::string mess) : Exception(mess) {}
};

class Collision : public Exception {
public:
  Collision(std::string mess) : Exception(mess) {}
};

#endif
