# JNI SDK for Minecraft Forge 1.7.10

This is an SDK that simplifies interacting with Minecraft Forge 1.7.10 through JNI. It is designed for developers creating native mods (or cheats, wink wink). While this SDK only supports version 1.7.10, you are welcome to use and modify it as you wish. I myself will not be adding other mappings or a modular mappings system.

---

## Quick Start

### Prerequisites

* JDK (required for JNI headers)
* Your project must link against `jvm.lib`

### Installation

* 'git clone' the repository or download the source code as a zip.
* Follow 'Building the Project' down below.

### Basic Usage

[Provide a simple code example demonstrating how to use the SDK]

---

## Structure

* **`include`**: This directory contains all header files for inclusion in your project.
* **`src`**: This directory contains all headers and cpp files required to build the project.
* **`dependency`**: This directory is where you will place the JNI headers from your JDK. These are required for the project to compile.

---

## Building the Project

1.  Obtain the JNI headers from your JDK and place them into the `dependency` directory.
2.  Run the `make` in the project's root directory to build a static library.

---

## Philosophy

This project contains both utility functions and `jobject` wrappers. The wrappers enclose a plain `jobject` and expose a certain Java API to the user, assuming the wrapped `jobject` matches the class whose API should be exposed.

**Getting Classes:** To receive java class references (`jclass`), use the Java::GetClass function. Do not use JNI's built-in FindClass function, as that cannot find classes loaded by Forge's class loader.

**Memory Management:** The wrappers never take ownership of object references. You are responsible for memory management: you retrieve a `jobject`, wrap it, operate on it, and then free the `jobject`. Everything returned is a local reference, unless the function name and documentation clearly state otherwise. Wrapper methods will never return other wrappers; they will return plain `jobjects` that you must then rewrap. This design ensures you are forced to explicitly handle and free all `jobjects` you receive.

**JVM Attachment:** `Java::Attach` should be called at the beginning of your logic and `Java::Detach` at the end. This attaches the calling thread to the JVM and initializes the `JNIEnv` pointer, which can then be retrieved with `Java::GetEnv`.

**Note:** Even when you are passed a `JNIEnv` pointer from a Java-called native function, you must still have called `Java::Attach` at least once because it initializes critical data needed for `Java::GetClass()` to function. This is not ideal and will be fixed in the future.

All functions and constructors require a `JNIEnv` pointer for JNI operations. If you are working from a native-only thread, always pass `Java::GetEnv()`. The parameter exists to allow usage from Java-called native code, where that JNIEnv pointer will be invalid.
All headers are well documented (hopefully)

---

## Known Issues

* Some things present in headers are not yet implemented. The function documentation will clearly state this. Do not use these functions as you will get a linkage error.
---

**If you have suggestions or bug reports, open an issue, a pull request or just modify the code yourself.**

Enjoy!
