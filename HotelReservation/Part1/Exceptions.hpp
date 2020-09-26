#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>

class InvalidRequest: public std::exception
{
  virtual const char* what() const noexcept
  {
      return "Bad Request\n";
  }
};

class InvalidCommand: public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Not Found\n";
    }
};

class InvalidAccess: public std::exception
{
  virtual const char* what() const noexcept
  {
    return "Permission Denied\n";
  }
};

class CreditShortage: public std::exception
{
  virtual const char* what() const noexcept
  {
    return "Not Enough Credit\n";
  }
};

class RoomShortage : public std::exception
{
  virtual const char* what() const noexcept
  {
    return "Not Enough Room\n";
  }
};

class NoRating : public std::exception
{
  virtual const char* what() const noexcept
  {
    return "No Rating\n";
  }
};
#endif
