#include "messages.h"

#include <memory.h>
#include <sstream>

// TODO what's the correct order of includes here?

// TODO use version from utils.h (but this will need to go somewhere common to all projects)
namespace
{

template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

}
/// internal enum to identify unique messages
enum class MessageType
{
  TraderKeyLogin,
  OrderInsert
};

/// auto generated serialisation routines
namespace {

template<typename T>
void Write(char*& buffer, const T& value)
{
    memcpy(buffer, &value, sizeof(T));
    buffer += sizeof(T);
}

template<>
void Write(char*& buffer, const std::string& value)
{
    static constexpr size_t ALIGNMENT = 4; // bytes
    memcpy(buffer, value.data(), value.size());
    const auto alignedSize = (value.size() + 1 /*nullchar*/ + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
    buffer += alignedSize;
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

void TraderKeyLoginMessage::Deserialise(char *buffer)
{
  // TODO: read each field back in and set
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

void OrderInsertMessage::Deserialise(char *buffer)
{
  // TODO: read each field back in and set
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
