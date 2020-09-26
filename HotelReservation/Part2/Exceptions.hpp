#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "Macros.hpp"
#include <exception>

class InvalidRequest: public std::exception
{
  virtual const char* what() const noexcept
  {
      return BAD_REQUEST;
  }
};

class InvalidCommand: public std::exception
{
    virtual const char* what() const noexcept
    {
        return NOT_FOUND;
    }
};

class InvalidAccess: public std::exception
{
  virtual const char* what() const noexcept
  {
    return PERMISSION_DENIED;
  }
};

class CreditShortage: public std::exception
{
  virtual const char* what() const noexcept
  {
    return NOT_ENOUGH_CREDIT;
  }
};

class RoomShortage : public std::exception
{
  virtual const char* what() const noexcept
  {
    return NOT_ENOUGH_ROOM;
  }
};

class NoRating : public std::exception
{
  virtual const char* what() const noexcept
  {
    return NO_RATING;
  }
};

class InsufficientRatings : public std::exception
{
  virtual const char* what() const noexcept
  {
    return INSUFFICIENT_RATINGS;
  }
};

#endif
