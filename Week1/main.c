#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

typedef enum
{
    false,
    true
} bool;

void strDowns(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if ('A' <= s[i] && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
}

int find(char *sorce, char *substr)
{
    char *dest = strstr(sorce, substr);
    int pos = dest - sorce;
    return pos;
}

bool isFirstLetterUpper(char *str)
{
    return (str[0] >= 'A' && str[0] <= 'Z');
}

bool isName(char *str, char *token)
{
    if (isFirstLetterUpper(token))
    {
        int pos = find(str, token);
        if (pos > 1 && pos < 300)
        {
            if (str[pos - 1] == ' ')
            {
                char punctuation[3] = {'.', '!', '?'};
                for (int i = 0; i < 3; i++)
                {
                    if (str[pos - 2] != punctuation[i] && str[pos - 3] != punctuation[i])
                    {
                        return true;
                    }
                }
            }
        }
        strDowns(token);
    }
    return false;
}

bool insertOrUpdate(treeType *root, char *token, int line)
{
    elementType data;
    strcpy(data.word, token);
    treeType temp = Search(*root, token);
    if (temp == NULL)
    {
        data.freq = 1;
        data.lines[0] = line;
    }
    else
    {
        for (int i = 0; i < temp->data.freq; i++)
        {
            data.lines[i] = temp->data.lines[i];
        }
        int freq = temp->data.freq + 1;
        data.freq = freq;
        data.lines[freq - 1] = line;
    }
    InsertNode(&(*root), data);
}

char **getStopw(char *textFile, int *line)
{
    *line = 0;
    FILE *fp = NULL;
    if ((fp = fopen(textFile, "r+")) == NULL)
    {
        printf("Can not open %s", textFile);
        return NULL;
    }
    char **str = malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        str[i] = malloc(30 * sizeof(char));
    }
    char str1[100];
    const char s[20] = "\r\n\t";
    char *token;
    while (fgets(str1, 50, fp))
    {
        token = strtok(str1, s);
        strcpy(str[*line], token);
        *line += 1;
    }
    fclose(fp);
    return str;
}

bool checkStop(char *token, char **str, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(token, str[i]) == 0)
            return false;
    }
    return true;
}

bool readTxtAndParse(char *textFile, char *stopFile, treeType *root)
{
    int count;
    char **stop = getStopw(stopFile, &count);
    FILE *fp = NULL;
    if ((fp = fopen(textFile, "r+")) == NULL)
    {
        printf("Can not open %s", textFile);
        return false;
    }
    int line = 0;
    char str[2000];
    const char s[20] = " -;:`!?.,()\"\r\n\t";
    char *token;
    while (fgets(str, 300, fp))
    {
        line++;
        char tmp[2000];
        strcpy(tmp, str);
        token = strtok(str, s);
        // printf(" - line %d : %s\n", line, tmp);
        while (token != NULL)
        {
            if (!isName(tmp, token) && checkStop(token, stop, count))
            {
                insertOrUpdate(root, token, line);
            }
            if(isName(tmp, token))
            {
                insertOrUpdate(root, token, line);
            }
            token = strtok(NULL, s);
        }
    }
    fclose(fp);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("./<name> <sorce>(vanban.txt, alice30.txt)  <dest>(solution.txt)\n");
        printf("  (!) Do not use stopw.txt as a parameter!!\n");
        return 1;
    }
    FILE *fp = NULL;
    if ((fp = fopen(argv[2], "w+")) == NULL)
    {
        printf("Can not open %s", argv[2]);
        return 2;
    }
    elementType element;
    treeType root;
    MakeNullTree(&root);
    printf("   [!]   Reading data from %s ...\n", argv[1]);
    printf("   [!]   Parsing data ...\n");
    readTxtAndParse(argv[1], "stopw.txt", &root);
    printf("   [!]   Writing data to %s ...\n", argv[2]);
    inOrderPrintFile(root, fp);
    printf(" (!) Done!!\n");

    return 0;
}