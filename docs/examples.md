 

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
#include "RenderWell/EBook.hpp"

#include <string>

... in function
BackendManager controller = BackendManager();
DataBase& dataBase = controller.getDataBaseRef();

std::vector<unsigned long> bookIds = dataBase.getBookIds();

for(auto bookId : bookIds)
{
    auto book = dataBase.getDataObjectRefAs<EBook>(bookId);

    some_function_that_needs_name_string(book.m_Name);
}
...

```

```cpp
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_examples/lv_apps/demo/demo.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "RenderWell/Types.hpp" // Include Types.hpp file
#include "RenderWell/BackendManager.hpp" // Include BackendManager.hpp file

class GUI {
public:
    GUI()
    : m_Controller(RenderWell::BackendManager())
    {
    }

    void sortLibraryAtoZ() {
    // Use the SortAtoZ type from Types.hpp for sorting
    std::vector<unsigned long> uuidList = m_Controller.sort(RenderWell::k_AtoZ);

    // Update GUI to show the new UUID list ordering
    DataBase& dataBase = controller.getDataBaseRef();

    std::vector<unsigned long> bookIds = dataBase.getBookIds();

   for(auto bookId : bookIds)
    {
        auto book = dataBase.getDataObjectRefAs<EBook>(bookId);

        display_name(EBook.m_Name);
    }

    // Implement LVGL code to update your eBook icons based on the UUID list
    }

private:
    BackendManager m_Controller;
};

int main(int argc, char* argv[]) {
    // Initialize LVGL and set up display driver
    lv_init();

    // Set up the display driver (replace with your driver configuration)
    fbdev_init();

    // Create a simple LVGL button for sorting
    lv_obj_t* button = lv_btn_create(lv_scr_act());
    lv_btn_set_fit(button, LV_FIT_TIGHT);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, "Sort A-Z");

    GUI gui = GUI();
    
    // Assign an event handler for the button
    lv_obj_set_event_cb(button, [](lv_obj_t*, lv_event_t event) {
        if (event == LV_EVENT_CLICKED) {
            if(button == AtoZButton)
            {
                gui.sortLibraryAtoZ();
            }
        }
    });

    // Main loop
    while (1) {
        lv_task_handler();
        usleep(5000); // Sleep for a while to control the loop rate
    }

    return 0;
}
```
