#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <memory>

class IMessage
{
public:
  virtual ~IMessage() = default;

  /// Deserialisation routine
  virtual void Deserialise(const char*& buffer) = 0;

  /// Extraction routine
  virtual std::string GenerateLogMessage() const = 0;
};

/// simple message type
class TraderKeyLoginMessage final : public IMessage
{
private:
  std::string mTraderName;
  unsigned int mTraderIndex = 0;
  float mFooFactor = 0;

public:
  /// Constructors
  TraderKeyLoginMessage() = default;
  TraderKeyLoginMessage(const TraderKeyLoginMessage&) = default;
  TraderKeyLoginMessage(TraderKeyLoginMessage&&) = default;
  ~TraderKeyLoginMessage() = default;
  TraderKeyLoginMessage& operator=(const TraderKeyLoginMessage&) = default;

  /// Getters and setters
  const std::string& GetTraderName() const;
  void SetTraderName(const std::string& value);

  uint32_t GetTraderIndex() const;
  void SetTraderIndex(const uint32_t value);

  float GetFooFactor() const;
  void SetFooFactor(float value);

  /// Serialisation routine
  void Serialise(char *&buffer) const;

  /// Deserialisation routine
  void Deserialise(const char*& buffer) override;

  /// Extraction routine
  std::string GenerateLogMessage() const override;
};

/// simple message type
class OrderInsertMessage final : public IMessage
{
private:
  uint32_t mVolume;
  double mPrice = 0;

public:
  /// Constructors
  OrderInsertMessage() = default;
  OrderInsertMessage(const OrderInsertMessage&) = default;
  OrderInsertMessage(OrderInsertMessage&&) = default;
  ~OrderInsertMessage() = default;
  OrderInsertMessage& operator=(const OrderInsertMessage&) = default;

  /// Getters and setters
  uint32_t GetVolume() const;
  void SetVolume(const uint32_t value);

  double GetPrice() const;
  void SetPrice(double value);

  /// Serialisation routine
  void Serialise(char *&buffer) const;

  /// Deserialisation routine
  void Deserialise(const char*& buffer) override;

  /// Extraction routine
  std::string GenerateLogMessage() const override;
};

/// Message factory
std::unique_ptr<IMessage> CreateMessage(const int messageId);

#endif // MESSAGES_H
