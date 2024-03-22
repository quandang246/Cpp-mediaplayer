#include "MediaManagement.hpp"

int main()
{
    MediaManagement A;

    std::cout << "Welcome to QuanDang's Mediaplayer program!" << std::endl;

    while (true)
    {
        std::cout << "0 - Exit." << std::endl;
        std::cout << "1 - View Media files in that folder and all sub-folder (audio and video)" << std::endl;
        std::cout << "2 - Create new playlist" << std::endl;
        std::cout << "3 - Delete a playlist" << std::endl;
        std::cout << "4 - view all playlist" << std::endl;
        std::cout << "5 - Update playlist" << std::endl;

        int choice;
        std::cout << "Please enter your's choice: ";
        std::cin >> choice;

        // Clearing the input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            A.view_folder_list();
            break;
        case 2:
            A.createPL();
            break;
        case 3:
            A.deletePL();
            break;
        case 4:
            A.view_all_PL();
            break;
        case 5:
            A.update_PL();
            break;
        default:
            std::cout << "Invalid input, please try again!" << std::endl;
            break;
        }
    }
}
