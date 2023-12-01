#include "FlexGenerator.h"
using namespace std;

void FlexGenerator :: formatRules(){
    ruleFormatter.formatKeywordAndPunc("rules.txt");
    ruleFormatter.formatLowPriority("rules.txt");
    
    ruleNames = ruleFormatter.getRuleNames();
    formattedRules = ruleFormatter.getFormattedRules();

    defNames = ruleFormatter.getDefinitionNames();
    formattedDefs = ruleFormatter.getFormattedDefinitions();
}

void FlexGenerator :: writeTokensFile(){tokenFileWriter.writeTokens(ruleNames);}

void FlexGenerator :: writeLexFile(){
    lexWriter.writeDefinitionsSection();
    lexWriter.writeRegularDefinitions(defNames, formattedDefs);
    lexWriter.writeRegularExpressions(ruleNames, formattedRules);
}

void FlexGenerator :: writeMainFile(){
    mainFileWriter.writeMainFileImports();
    mainFileWriter.writeMainFileFunction(ruleNames);
}


int main(int argc, char** argv){
    FlexGenerator generator;
    generator.formatRules();
    generator.writeTokensFile();
    generator.writeLexFile();
    generator.writeMainFile();
}
