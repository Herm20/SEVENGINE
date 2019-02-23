# SEVENGINE

## Coding Standards

### Coding Style

Class, method, function, and other such entities are named with pascal case.

Variable names are named with camel case.

Curly braces on a new line.

`private` before `protected` before `public`; match order in source files.

Tabs for spaces, except when matching indentation.

```cpp
void Foo(u64 arg)
{
	Bar(arg,
	    true,
	    nullptr);
}
```

### Best Practices

Use define blocks instead of `#pragma once` for header guards.

```cpp
#ifndef HEADER_NAME_H_
#define HEADER_NAME_H_

// Header file contents

#endif
```

Use constructor initializater lists.

```cpp
MyClass::MyClass(u64 arg) :
	memberVariable(arg)
{
	// Possibly do something here
}
```

Use `const` and `inline` where applicable.

```cpp
inline u64 GetVar() const { return memberVariable; }
```

Limit includes as much as possible.

### Engine Preferences

Use the fixed-size numeric types defined in `types.h`.

Do not perform raw IO outside of specifically designated engine subsystems.

We will be maintaining a Linux build, with full intention of this engine supporting cross-platform development. Don't break this with platform-specific code.

## Setting Up the Project

### GLM

When including glm in a file, ensure that you `#define GLM_ENABLE_EXPERIMENTAL` before the GLM includes. The basic 3D maths GLM include section would look like :

```cpp
#define GLM_ENABLE_EXPERIMENTAL
#include "../glm/glm.hpp"
#include "../glm/gtx/quaternion.hpp"
```

### Boost

_Note : this guide is primarily targeted at setting up a Windows development environment. You can probably just use your package manager on Linux._

1. Download boost at : https://www.boost.org/users/history/version_1_69_0.html

2. Extract into the `Engine` project directory

3. Run `bootstrap.bat` or `bootstrap.sh` depending on your development environment

4. Run the newly generated `b2` executable (this will take a while)

5. (Visual Studio) Go to your project properties, and set Configuration and Platform options to All

6. (Visual Studio) Add `$(ProjectDir)Engine\boost_1_69_0` to `Include Directories`

7. (Visual Studio) Add `$(ProjectDir)Engine\boost_1_69_0\stage\lib` to `Library Directories`
