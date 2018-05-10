#include "database_utility.h"

/*************************************  User input  *************************************/

Params mainArguments(char *argv[])
{
    Params params;

    if((strcmp(argv[1], "-i") == 0) && (strcmp(argv[3], "-n") == 0))
    {
        if(strstr(argv[2], ".txt") != NULL && isNumberValid(argv[4]) == 0)
        {
            strcpy( params.fileName , argv[2]);
            strcpy(params.seekNumber , argv[4]);
            return params;
        }

        else
            helpPrompt("Wartosc parametru jest nie poprawna.");
    }

    else if((strcmp(argv[1], "-n") == 0) && (strcmp(argv[3], "-i") == 0))
    {
        if(isNumberValid(argv[2]) == 0 && strstr(argv[4], ".txt") != NULL)
        {
            strcpy(params.seekNumber, argv[2]);
            strcpy(params.fileName, argv[4]);
            return params;
        }

        else
            helpPrompt("Wartosc parametru jest nie poprawna.");
    }

    else
        helpPrompt("Podano niewlasciwy argument.");
}

int isNumberValid(char *phoneNumber)
{
    if(strlen(phoneNumber) != 9)
        return -1;

    char *validChars = "0123456789*";
    char str[2] = "\0";

    for(int i = 0; i < strlen(phoneNumber); i++)
    {
        str[0] = phoneNumber[i];

        if(strstr(validChars, str) == NULL)
            return -1;
    }

    return 0;
}

void helpArgument(char *argv[])
{
    if(strcmp(argv[1], "-h") == 0)
        helpPrompt(NULL);
    else
        helpPrompt("Podano niewlasciwy argument.");
}

/*************************************  List management  *************************************/

Node *createNode(const Data data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));

    if(new_node == NULL)
    {
        puts("Blad podczas alokowania pamieci.");
        exit(0);
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

Node *pushToList(Node *head, const Data data)
{
    Node *new_node = createNode(data);

    if(head == NULL)
        head = new_node;

    else
    {
        Node *tmp = head;

        while(tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = new_node;
    }

    return head;
}

void deleteList(Node *head)
{
    if(head != NULL)
    {
        Node *current = head, *next;

        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = NULL;
            current = next;
        }

        head = NULL;
    }
}

/*************************************  File management  *************************************/

Node *parseDatabase(char *filePath, Node *head)
{
    FILE *file = fopen(filePath, "r");
    char buffer[255];

    if(file == NULL)
    {
        helpPrompt("Brak mozliwosci odczytu pliku. Plik nie istnieje.");
        exit(0);
    }

    while(fgets(buffer, 255, file) != 0)
        head = pushToList(head, parseFileLine(buffer));

    fclose(file);

    return head;
}

Data parseFileLine(char *buffer)
{
    Data data;
    int i = 0;

    char *token = strtok(buffer, ";\n");

    while(token != NULL)
    {
        if(i == 0)
            strcpy(data.user, token);

        else
            strcpy(data.phone_number, token);

        token = strtok(NULL, "; \n");
        i++;
    }

    return data;
}

/*************************************  User output  *************************************/

void helpPrompt(char *message)
{
    if(message)
        printf("\nError: %s\n\n", message);

    puts("Sposob uzycia:\n");
    puts(" Baza -i [nazwa_pliku] -n [numer_telefonu]");
    puts("");
    puts("Argumenty:\n");
    puts(" -i\t: podaj sciezka do pliku");
    puts(" -n\t: podaj numer telefonu do znalezienia\n");
    puts("albo\n");
    puts(" -h\t: aby wyswietlic pomoc\n");
}

void databaseSearch(Node *head, char *phoneNumber)
{
    Node *tmp = head;
    int i = 0, flag = 0, result = 0;

    printf("\nWyniki wysukiwania dla numeru: %s\n", phoneNumber);

    while(tmp != NULL)
    {
        while(i < 9 && flag == 0)
        {
            if((phoneNumber[i] != tmp->data.phone_number[i]) &&  phoneNumber[i] != '*')
                flag++;

            i++;
        }

        if(flag == 0)
        {
            printf("\n %s\n", tmp->data.user);
            printf(" %s\n", tmp->data.phone_number);
        }

        if(flag == 0)
            result++;

        i = 0, flag = 0;
        tmp = tmp->next;
    }

    if(result == 0)
        puts("Podany numer nieznajduje sie w bazie.");
}
