# Overview

This repository provides `groov` definitions for STM32 device peripherials. `groov` allows
easy composition and "specialization" by creating type aliases.

For more information about `groov`, see https://github.com/intel/generic-register-operation-optimizer

# How it works

The STM32 family of micros has a rich set of peripherials and the ecosystem has a large variety of devices. Fortunately, the peripherials appear to be reused across devices with the same register layouts and functionality. The mixture of which peripherials exist and the memory map changes for each. Luckily, we can model this perfectly with `groov`.

The stm32-groov library defines peripherials individually and then composes them together per device at the correct memory location. This composition is performed using `groov`'s `group` definition.

Including one of the device headers, such as `stm32l432.hpp`, will pull in the enabled peripherials at the correct base addresses for the device. The type and a value are available in the `caisselabs::stm32` namespace. For example, for the `stm32l432`, there are both `usart1_t` and `usart2_t` types that have `usart1` and `usart2` values.

Register and field names try to track the documentation closely so that it is not too difficult to map things.


# Usage

## CPM

This repository will pull in dependencies via CPM ([CMake Package Manager](https://github.com/cpm-cmake/CPM.cmake)) and is setup to be friendly to include in your own projects via CPM.

You can use CPM to pull in the package at a specified SHA, tag, or branch. For example, add in your `CMakeLists.txt`

```cmake
cpmaddpackage("gh:caisselabs/stm32-groov#develop")
```

Transitive dependencies such as `groov`, Intel's baremetal-senders-receivers library, and `stdx` will also be fetched when cmake build files are generated.

Just add `stm32-groov` as a link library:

```cmake
target_link_libraries(my_prog PUBLIC stm32-groov)
```

