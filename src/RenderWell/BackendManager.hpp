#pragma once

#include "DataBase.hpp"

namespace RenderWell
{
    class BackendManager
    {
    public:
        BackendManager();
        ~BackendManager() noexcept = default;

        BackendManager(const BackendManager& obj) = default;
        BackendManager(BackendManager&& obj) noexcept = default;

        BackendManager& operator=(const BackendManager& obj) = default;
        BackendManager& operator=(BackendManager&& obj) = default;

        void writeOut()
        {
            // write state (all member variables to disk)
        }

        void sendUpdate(Interaction)
        {
            std::string commandString;
            // convert interaction via switch
            {
                Option 1: set string to reload from library list
            }
// append associated UUID/Map ID to command string so GUI can verify it
// appears
        }

        void processUpdate(string)
        {
// Try catch here to handle errors
            try{
                std::string commandString;
                // convert interaction via switch and update string with change keys

// Call to sendUpdate() with commandString to decipher and send changes to
// GUI
            } catch (std::runtime_exception e)
            {
                // process and display errors that were caught after writing log file
            }
        }

        void removeWrapper(unsigned long, unsigned long)
        {
// Wrapper function for creating temp ListManager to remove ebook from list
        }

        void addWrapper(unsigned long, unsigned long)
        {
            // Wrapper function for creating temp ListManager to add ebook to list
        }

        void updateSettingWrapper(string, string)
        {
            //
        }

        void renameWrapper(unsigned long)
        {
            // Wrapper function for creating temp ListManager to rename ebook or list
        }

        void add(unsigned long) // repeatedly called on start up for multithreading safety
        {
            // Make threadsafe
            // add ebook the member variable m_EBooks
        }

        std::vector<unsigned long> sort(unsigned char)
        {
            // create temp Sorter instance to sort List
        }

        unsigned long find(bool, string)
        {
            // searches m_EBooks for a matching title and returns uuid of EBook object
        }

    private:
    DataBase m_DataBase;
    };
}