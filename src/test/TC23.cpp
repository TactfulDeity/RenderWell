#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"
#include "RenderWell/render_well_directories.hpp"

namespace
{
    const std::string k_TempName = "Temp";
}
    
TEST_CASE("TC23: Set Directory:", "[Settings]")
{
    BackendManager controller = BackendManager();

    controller.updateSettingWrapper(k_InputDirKey,"/");
    
    std::string initialDir = controller.getSetting(k_InputDirKey);
    
    controller.updateSettingWrapper(k_InputDirKey, k_DataFilesDir);
    
    std::string newDir = controller.getSetting(k_InputDirKey);

    REQUIRE(initialDir != newDir);

}