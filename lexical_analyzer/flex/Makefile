#Generating OutputFile
FLEX: RuleFormatter.o TokenFileWriter.o LexWriter.o main.o
	g++ -o $@ $^

#Generating Object File from CPP file.
%.o:%.cpp
	g++ -o $@ -c $<