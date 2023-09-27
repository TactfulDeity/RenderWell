namespace
{
    const std::string k_DefaultSettingName = "Default";
    const std::string k_ThemeSettingName = "Theme";
}
    
TEST_CASE("TC24: Clear Settings:, "[Settings]")
{
    app.addSetting(::k_ThemeSettingName, "Dark");
    const std::string themeType = app.getSetting(::k_ThemeSettingName);
    app.clearSettings();
    REQUIRE(app.getSetting::k_ThemeSettingName) == ::k_DefaultSettingName);
}