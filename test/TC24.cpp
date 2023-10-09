#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

namespace
{
    const std::string k_DefaultSettingName = "Default";
    const std::string k_ThemeSettingName = "Theme";
}
    
TEST_CASE("TC24: Clear Settings:", "[Settings]")
{
    BackendManager controller = BackendManager();

    controller.addSetting(::k_ThemeSettingName, "Dark");
    
    const std::string themeType = controller.getSetting(::k_ThemeSettingName);
    
    controller.clearSettings();
    
    REQUIRE(controller.getSetting::k_ThemeSettingName) == ::k_DefaultSettingName);
}