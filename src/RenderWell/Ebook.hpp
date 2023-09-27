struct Ebook
{
    std::string m_Title;
    std::string m_Author;
    unsigned long m_UUID;
    std::vector<unsigned long> m_Lists;
    std::path m_Location;
} 