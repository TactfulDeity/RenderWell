#include "Types.hpp"

template<typename Sort = SortFavorites>
Class Sorter
{
public:
    // Declare Constructor and Destructor
    Sorter()
    {

    }
    ~Sorter() noexcept = default;
    // Declare copy and move constructors

    std::vector<unsigned long> operator()()
    {
        // queries library list and sorts according to m_SortType
 
        // returns a vector of the sorted id list
    } 

private: 
    Sort m_SortType;
    constexpr unsigned long m_FavoritesUUID;
}