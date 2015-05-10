#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

/// simple message type
class TraderKeyLoginMessage final
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

  /// Message type
  uint32_t GetMessageType() const;

  /// Serialisation routine
  void Serialise(char *&buffer) const;

  /// Extraction routine
  std::string GenerateLogMessage() const;
};

/// simple message type
class OrderInsertMessage final
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

  /// Message type
  uint32_t GetMessageType() const;

  /// Serialisation routine
  void Serialise(char *&buffer) const;

  /// Extraction routine
  std::string GenerateLogMessage() const;
};

#endif // MESSAGES_H
