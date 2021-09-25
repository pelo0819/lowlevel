#pragma once
#ifndef __INCLUDE_PELOPARSER_H__
#define __INCLUDE_READPARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>

typedef struct
{
    int idx;
    char name[256];
} Table;

class PeloParser
{
private:
    std::list<Table *> lstMachine;
    std::list<Table *> lstAbi;
    std::list<Table *> lstSectionType;
    std::list<Table *> lstProgramType;
    std::list<Table *> lstSymbolScope;
    std::list<Table *> lstSymbolType;
    std::list<Table *> lstRelocationType;
public:
    PeloParser();
    ~PeloParser();
    void setup();
    void parse(FILE *file, std::list<Table *> &lst);
    void parse(FILE *file, std::list<Table *> **lst);
    void parseLstMachine();
    void parseLstAbi();
    void parseLstSectionType();
    void parseLstProgramType();
    void parseLstSymbolScope();
    void parseLstSymbolType();
    void parseLstRelocationType();
    void printLst(std::list<Table *> &lst);
    char *getValue(int key, std::list<Table *> &lst);
    std::list<Table *> &getLstMachine(){ return lstMachine; }
    std::list<Table *> &getLstAbi(){ return lstAbi; }
    std::list<Table *> &getLstSectionType(){ return lstSectionType; }
    std::list<Table *> &getLstProgramType(){ return lstProgramType; }
    std::list<Table *> &getLstSymbolScope(){ return lstSymbolScope; }
    std::list<Table *> &getLstSymbolType(){ return lstSymbolType; }
    std::list<Table *> &getLstRelocationType(){ return lstRelocationType; }
};


#endif