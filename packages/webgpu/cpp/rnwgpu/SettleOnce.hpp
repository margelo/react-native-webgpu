//
//  SettleOnce.hpp
//  Pods
//
//  Created by Ritesh Shukla on 04/10/26.
//

#pragma once

#include <atomic>
#include <exception>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <NitroModules/NitroLogger.hpp>
#include <NitroModules/Promise.hpp>

namespace rnwgpu {

template <typename T> class SettleOnce {
public:
  explicit SettleOnce(std::string operation)
      : _operation(std::move(operation)),
        _promise(margelo::nitro::Promise<T>::create()) {}

  static std::shared_ptr<SettleOnce> create(std::string operation) {
    return std::make_shared<SettleOnce>(std::move(operation));
  }

  std::shared_ptr<margelo::nitro::Promise<T>> promise() const {
    return _promise;
  }

  template <typename Body> void settle(Body &&body) noexcept {
    std::exception_ptr error;
    if constexpr (std::is_void_v<T>) {
      try {
        std::forward<Body>(body)();
      } catch (...) {
        error = std::current_exception();
      }
      finish(error, [this] { _promise->resolve(); });
    } else {
      std::optional<T> result;
      try {
        result.emplace(std::forward<Body>(body)());
      } catch (...) {
        error = std::current_exception();
      }
      finish(error, [&] { _promise->resolve(std::move(*result)); });
    }
  }

private:
  template <typename Resolve>
  void finish(std::exception_ptr error, Resolve &&resolve) noexcept {
    if (_settled.exchange(true)) {
      return;
    }
    try {
      if (error) {
        _promise->reject(asStandardException(error));
      } else {
        resolve();
      }
    } catch (...) {
      logSettleFailure();
    }
  }

  std::exception_ptr asStandardException(std::exception_ptr error) const {
    try {
      std::rethrow_exception(error);
    } catch (const std::exception &) {
      return error;
    } catch (...) {
      return std::make_exception_ptr(
          std::runtime_error(_operation + ": unknown native error"));
    }
  }

  void logSettleFailure() noexcept {
    try {
      margelo::nitro::Logger::nativeLog(margelo::nitro::LogLevel::Error,
                                        "SettleOnce",
                                        _operation + ": failed to settle");
    } catch (...) {
    }
  }

  std::string _operation;
  std::shared_ptr<margelo::nitro::Promise<T>> _promise;
  std::atomic<bool> _settled{false};
};

} // namespace rnwgpu
