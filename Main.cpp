/*
*   Joshua Thornton
*   Binary Search Tree
*   Started: 11/30/2021
*   Last Edited: 12/03/2021
*/

#pragma region Preprocessor Directives
// Includes the AppDriver class.
#include "AppDriver.h"
#pragma endregion Preprocessor Directives

int main()
{
    // Create an AppDriver object to run the show.
    AppDriver appDriver = AppDriver();
    // Run the Intro scenario, then the RunTests scenario.
    appDriver.Intro();
    appDriver.RunTests();

    // Return 0 to show that the program ran with no error.
    return 0;
}
