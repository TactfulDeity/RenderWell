class Settings
{
public:
std::Map<unsigned long, string> m_SettingsMap;

    // Declare Constructor and Destructor
    // Declare copy and move constructors

    void updateSetting(unsigned long settingId, std::string updatevalue)
{
        // write the update value to the corresponding slot in the settings.json file 

        // update the in memory settings map
    } 

private: 
    std::filesystem::path m_Location
}