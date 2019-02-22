# SEVENGINE

## Coding Standards

### Coding Style

Class, method, function, and other such entities are named with pascal case.

Variable names are named with camel case.

Determine how we're handling open curly braces (same line versus next line).

### Best Practices

Use define blocks instead of `#pragma once` for header guards.

Use constructor initializater lists.

Use `const` and `inline` where applicable.

Limit includes as much as possible.

### Engine Preferences

Use the fixed-size numeric types defined in `types.h`.

Do not perform raw IO outside of specifically designated engine subsystems.

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

5. (Visual Studio) Go to your project properties and add `$(ProjectDir)Engine\boost_1_69_0` to `Include Directories`

6. (Visual Studio) In the same place, add `$(ProjectDir)Engine\boost_1_69_0\stage\lib` to `Library Directories`