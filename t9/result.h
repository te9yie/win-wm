#pragma once
#include <cassert>
#include <optional>

namespace t9 {

/// @brief Result 用無効値.
constexpr inline std::nullopt_t none = std::nullopt;

/// @brief 戻り値を少し便利に扱うクラス
template <typename T>
class Result {
 private:
  std::optional<T> value_;

 public:
  Result() = default;
  Result(std::nullopt_t) : value_(std::nullopt) {}
  Result(T value) : value_(std::move(value)) {}

  /// @brief bool への明示的な型変換
  explicit operator bool() const { return value_.has_value(); }

  /// @brief 正常値の取り出し (Move)
  T unwrap() {
    assert(value_);
    return std::move(value_.value());
  }
};

/// @brief ポインタ用 Result
template <typename T>
class Result<T*> {
 private:
  T* ptr_ = nullptr;

 public:
  Result(std::nullptr_t) : ptr_(nullptr) {}
  Result(T* p) : ptr_(p) {}

  /// @brief bool への明示的な型変換
  explicit operator bool() const { return !!ptr_; }

  /// @brief ポインタ参照
  T* operator->() const {
    assert(ptr_);
    return ptr_;
  }

  /// @brief 正常値の取り出し
  T* unwrap() const {
    assert(ptr_);
    return ptr_;
  }
};

/// @brief bool 用 Result
template <>
class Result<bool> {
 private:
  bool value_ = false;

 public:
  Result() : value_(false) {}
  Result(bool value) : value_(value) {}

  /// @brief bool への明示的な型変換
  explicit operator bool() const { return value_; }

  /// @brief 正常値の取り出し
  bool unwrap() const {
    assert(value_);
    return value_;
  }
};

}  // namespace t9