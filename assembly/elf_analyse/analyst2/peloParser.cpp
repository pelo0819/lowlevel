#include "peloParser.h"

PeloParser::PeloParser(){}

PeloParser::~PeloParser(){}

void PeloParser::setup()
{
    parseLstMachine();
    parseLstAbi();
    parseLstSectionType();
    parseLstProgramType();
    parseLstSymbolScope();
    parseLstSymbolType();
    parseLstRelocationType();
}

void PeloParser::parse(FILE *fp, std::list<Table *> &lst)
{
    if(fp == NULL)
    {
        printf("err open file\n");
    }

    char str[128];
    while (fgets(str, 128, fp) != NULL)
    {
        char *ptr = strtok(str, "\t");
        int idx = atoi(ptr);
        ptr = strtok(NULL, "\t");
        char *p = strchr(ptr, '\n');
        if(p != NULL){*p = '\0';}

        Table *t  = new Table();
        t->idx = idx;
        strcpy(t->name, ptr);
        lst.push_back(t);
    }
}

void PeloParser::parse(FILE *fp, std::list<Table *> **lst)
{
    if(fp == NULL)
    {
        printf("err open file\n");
    }

    char str[128];
    while (fgets(str, 128, fp) != NULL)
    {
        char *ptr = strtok(str, "\t");
        int idx = atoi(ptr);
        ptr = strtok(NULL, "\t");
        char *p = strchr(ptr, '\n');
        if(p != NULL){*p = '\0';}

        Table *t  = new Table();
        t->idx = idx;
        strcpy(t->name, ptr);
        (*lst)->push_back(t);
    }
}

void PeloParser::parseLstMachine()
{
    FILE *fp;
    fp = fopen("resources/e_machine_list.pelo", "r");
    parse(fp, lstMachine);
    fclose(fp);
}

void PeloParser::parseLstAbi()
{
    FILE *fp;
    fp = fopen("resources/os_abi_list.pelo", "r");
    parse(fp, lstAbi);
    fclose(fp);
}

void PeloParser::parseLstSectionType()
{
    FILE *fp;
    fp = fopen("resources/s_header_type_list.pelo", "r");
    parse(fp, lstSectionType);
    fclose(fp);
}

void PeloParser::parseLstProgramType()
{
    FILE *fp;
    fp = fopen("resources/p_header_type_list.pelo", "r");
    parse(fp, lstProgramType);
    fclose(fp);
}

void PeloParser::parseLstSymbolScope()
{
    FILE *fp;
    fp = fopen("resources/symbol_scope_lsit.pelo", "r");
    parse(fp, lstSymbolScope);
    fclose(fp);
}

void PeloParser::parseLstSymbolType()
{
    FILE *fp;
    fp = fopen("resources/symbol_type_list.pelo", "r");
    parse(fp, lstSymbolType);
    fclose(fp);
}

void PeloParser::parseLstRelocationType()
{
    FILE *fp;
    fp = fopen("resources/relocation_type_list.pelo", "r");
    parse(fp, lstRelocationType);
    fclose(fp);
}

char *PeloParser::getValue(int key, std::list<Table *> &lst)
{
    std::list<Table *>::iterator it = lst.begin();
    while (it != lst.end())
    {
        if((*it)->idx == key)
        {
            return (*it)->name;
        }
        it++;
    }
    return NULL;
}

void PeloParser::printLst(std::list<Table *> &lst)
{
    std::list<Table *>::iterator it = lst.begin();
    while (it != lst.end())
    {
        printf("idx: %d, val: %s\n", (*it)->idx, (*it)->name);
        it++;
    }
}