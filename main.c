#include "database_utility.h"

int main(int argc, char *argv[])
{
    Params params;
    Node *head = NULL;

    switch(argc)
    {
        case 2:
            helpArgument(argv);
            break;

        case 5:
            params = mainArguments(argv);

            if(params.fileName != NULL && params.seekNumber != NULL)
            {
                head = parseDatabase(params.fileName, head);

                if(head != NULL)
                {
                    databaseSearch(head, params.seekNumber);
                    deleteList(head);
                }

                else
                    helpPrompt("Plik z danymi jest pusty.");
            }

            break;

        default:
            helpPrompt("Podano niewlasciwa liczbe argumentow.");
            break;
    }

    return 0;
}
