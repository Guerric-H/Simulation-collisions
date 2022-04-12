CPP = g++
FLAGS = -Wall -O3
LINK_EXEC = -o main main.cpp 
EXEC = ./main
R = R CMD BATCH
RM = rm -f


run : all

all: compile
	./main all
	$(R) standard.R
	$(R) confiance.R
	$(R) histogramme.R
	$(R) collision.R
compile: 
	$(CPP) $(FLAGS) $(LINK_EXEC)

standard: clean_stand compile
	$(EXEC) standard
	$(R) standard.R

confiance: clean_conf compile 
	$(EXEC) confiance
	$(R) confiance.R

histogramme: clean_histo compile
	$(EXEC) histogramme
	$(R) histogramme.R


collision: clean_collis compile
	$(EXEC) collision
	$(R) collision.R
	$(R) e2_90succes.R

clean_stand: 
	$(RM) -f standard.txt standard.Rout standard.pdf

clean_conf: 
	$(RM) -f confiance.txt confiance.Rout confiance.pdf

clean_histo: 
	$(RM) -f hist*.txt histogramme.Rout histogramme.pdf

clean_collis: 
	$(RM) -f collisions.txt collision.Rout e2_90succes.Rout e2_90succes.pdf collision.pdf 

clean : 
	$(RM) -f *.txt main *.Rout 

clean_w_pdf:
	$(RM) -f *.txt main *.Rout *.pdf

