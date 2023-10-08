 

 ## Sorting Example

 ```cpp
#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"

... in function
BackendManager controller = BackendManager();

if(sortAtoZSignal)
{
    std::vector<unsigned long> uuidList = controller.sort(k_AtoZ);

    // update gui to just show new UUID list ordering
}
...

```

## DataBase Parsing Example

```cpp
#include "RenderWell/BackendManager.hpp"
#include "RenderWell/DataBase.hpp"

... in function
BackendManager controller = BackendManager();

if(sortAtoZSignal)
{
    std::vector<unsigned long> uuidList = controller.sort(k_AtoZ);

    // update gui to just show new UUID list ordering
}
...

```
