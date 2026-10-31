//
//  WebGPUObject.hpp
//  ReactNativeWebGPU
//
//  Created by Dave Mkpa-Eke on 31/10/2026.
//

#pragma once

#include <memory>
#include <string>

#include <NitroModules/HybridClass.hpp>
#include <NitroModules/HybridObject.hpp>
#include <jsi/jsi.h>

namespace rnwgpu {

namespace jsi = facebook::jsi;
using margelo::nitro::HybridClass;
using margelo::nitro::HybridObject;

// Base for every WebGPU HybridObject: adds `__brand`, `toJSON` and
// `toString()` on top of the nitrogen-generated `Spec`, like NativeObject.
template <typename Spec> class WebGPUObject : public Spec {
public:
  struct Class {
    using Base = typename Spec::Class;
    static constexpr const char *name = Spec::Class::name;
    static const std::shared_ptr<const HybridClass> &get() {
      static const auto hybridClass =
          HybridClass::create<Class>([](HybridClass &clazz) {
            clazz.registerHybridProperty("__brand", &HybridObject::getName);
            clazz.registerRawHybridMethod("toJSON", 0, &WebGPUObject::toJSON);
          });
      return hybridClass;
    }
  };

  std::string toString() override { return "[object " + this->getName() + "]"; }

protected:
  const std::shared_ptr<const HybridClass> &getHybridClass() override {
    return Class::get();
  }

  size_t getExternalMemorySize() noexcept override { return 1024; }

private:
  // Data properties are getters on the prototype chain, which JSON.stringify
  // does not serialize, so collect them like NativeObject's toJSON.
  jsi::Value toJSON(jsi::Runtime &runtime, const jsi::Value &thisValue,
                    const jsi::Value * /*args*/, size_t /*count*/) {
    auto self = thisValue.getObject(runtime);
    auto object = runtime.global().getPropertyAsObject(runtime, "Object");
    auto getPrototypeOf =
        object.getPropertyAsFunction(runtime, "getPrototypeOf");
    auto getOwnPropertyNames =
        object.getPropertyAsFunction(runtime, "getOwnPropertyNames");
    auto objectPrototype = object.getProperty(runtime, "prototype");

    jsi::Object json(runtime);
    auto prototype = getPrototypeOf.call(runtime, self);
    while (prototype.isObject() &&
           !jsi::Value::strictEquals(runtime, prototype, objectPrototype)) {
      auto names = getOwnPropertyNames.call(runtime, prototype)
                       .getObject(runtime)
                       .getArray(runtime);
      for (size_t i = 0; i < names.size(runtime); i++) {
        auto name =
            names.getValueAtIndex(runtime, i).getString(runtime).utf8(runtime);
        if (isSkipped(name) || json.hasProperty(runtime, name.c_str())) {
          continue;
        }
        auto value = self.getProperty(runtime, name.c_str());
        if (value.isObject() && value.getObject(runtime).isFunction(runtime)) {
          continue;
        }
        json.setProperty(runtime, name.c_str(), value);
      }
      prototype = getPrototypeOf.call(runtime, prototype);
    }
    return json;
  }

  // `__type` is the prototype name Nitro adds in debug builds.
  static bool isSkipped(const std::string &name) {
    return name == "constructor" || name == "toJSON" || name == "__type";
  }
};

} // namespace rnwgpu
