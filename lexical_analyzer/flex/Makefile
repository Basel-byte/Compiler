#Generating CPP File from LEX FILE
%.cpp:%.l
	flex -o $@ $<

#Generating Compiled Progrma
FLEX: main.o flex.o
	g++ -o $@ $^

#Running the automated code to import rules to flex
FLEX_File_Gen: RuleFormatter.o TokenFileWriter.o LexWriter.o MainFileWriter.o FlexGenerator.o
	g++ -o $@ $^

#Generating Object File from CPP file.
%.o:%.cpp
	g++ -o $@ -c $<

#Generating CPP File from LEX file.
%.o:%.cpp
	g++ -o $@ -c $<