#include "messages.h"

#include <memory.h>
#include <sstream>

// TODO what's the correct order of includes here?

namespace
{
  // TODO use version from utils.h (but this will need to go somewhere common to all projects)
  template <typename T, typename... Ts>
  std::unique_ptr<T> make_unique(Ts&&... params)
  {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
  }

  /// internal enum to identify unique messages
  enum class MessageType
  {
    TraderKeyLogin,
    OrderInsert
  };

  constexpr size_t ALIGNMENT = 4; // bytes

  constexpr size_t GetAlignedSize(const size_t unalignedSize)
  {
    return (unalignedSize + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
  }

  /// "auto generated" serialisation routines
  template<typename T>
  void Write(char*& buffer, const T& value)
  {
    memcpy(buffer, &value, sizeof(T));
    buffer += sizeof(T);
  }

  template<>
  void Write(char*& buffer, const std::string& value)
  {
    memcpy(buffer, value.data(), value.size());
    buffer += GetAlignedSize(value.size() + 1 /*nullchar*/);
  }

  template<typename T>
  void Read(const char*& buffer, T& value)
  {
    memcpy(&value, buffer, sizeof(T));
    buffer += sizeof(T);
  }

  template<>
  void Read(const char*& buffer, std::string& value)
  {
    value.assign(buffer);
    buffer += GetAlignedSize(value.size() + 1 /*nullchar*/);
  }
}

const std::string& TraderKeyLoginMessage::GetTraderName() const
{
  return mTraderName;
}

void TraderKeyLoginMessage::SetTraderName(const std::string& value)
{
  mTraderName = value;
}

uint32_t TraderKeyLoginMessage::GetTraderIndex() const
{
  return mTraderIndex;
}

void TraderKeyLoginMessage::SetTraderIndex(const uint32_t value)
{
  mTraderIndex = value;
}

float TraderKeyLoginMessage::GetFooFactor() const
{
  return mFooFactor;
}

void TraderKeyLoginMessage::SetFooFactor(float value)
{
  mFooFactor = value;
}

void TraderKeyLoginMessage::Serialise(char*& buffer) const
{
  Write(buffer, MessageType::TraderKeyLogin);
  Write(buffer, mTraderName);
  Write(buffer, mTraderIndex);
  Write(buffer, mFooFactor);
}

void TraderKeyLoginMessage::Deserialise(const char *& buffer)
{
  Read(buffer, mTraderName);
  Read(buffer, mTraderIndex);
  Read(buffer, mFooFactor);
}

std::string TraderKeyLoginMessage::GenerateLogMessage() const
{
  std::ostringstream logMessage;
  logMessage << "Trader key login, trader: " << mTraderName;
  logMessage << ", index: " << mTraderIndex;
  logMessage << ", Foo: " << mFooFactor;
  return logMessage.str();
}

uint32_t OrderInsertMessage::GetVolume() const
{
  return mVolume;
}

void OrderInsertMessage::SetVolume(const uint32_t value)
{
  mVolume = value;
}

double OrderInsertMessage::GetPrice() const
{
  return mPrice;
}

void OrderInsertMessage::SetPrice(double value)
{
  mPrice = value;
}

void OrderInsertMessage::Serialise(char*& buffer) const
{
  Write(buffer, MessageType::OrderInsert);
  Write(buffer, mVolume);
  Write(buffer, mPrice);
}

void OrderInsertMessage::Deserialise(const char *& buffer)
{
  Read(buffer, mVolume);
  Read(buffer, mPrice);
}

std::string OrderInsertMessage::GenerateLogMessage() const
{
  std::ostringstream logMessage;
  logMessage << "Order inserted, volume: " << mVolume;
  logMessage << ", price: " << mPrice;
  return logMessage.str();
}

std::unique_ptr<IMessage> CreateMessage(const int messageId)
{
  switch (static_cast<MessageType>(messageId))
  {
    case MessageType::OrderInsert:
      return make_unique<OrderInsertMessage>();
    case MessageType::TraderKeyLogin:
      return make_unique<TraderKeyLoginMessage>();
  }
}
