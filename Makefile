CPP = g++
FLAGS = -Wall -O3
LINK_EXEC = -o main main.cpp 
everything = clean standard confiance histogramme collision


run : all

all: compile
	./main all
	R CMD BATCH standard.R
	R CMD BATCH confiance.R
	R CMD BATCH histogramme.R
	R CMD BATCH collision.R
compile: 
	$(CPP) $(FLAGS) $(LINK_EXEC)


standard: compile
	./main standard
	R CMD BATCH standard.R

confiance: compile
	./main confiance
	R CMD BATCH confiance.R

histogramme: compile
	./main histogramme
	R CMD BATCH histogramme.R

collision: compile
	./main collision
	R CMD BATCH collision.R

clean_stand: 
	rm standard.txt standard.Rout standard.pdf

clean_conf: 
	rm confiance.txt confiance.Rout confiance.pdf

clean_histo: 
	rm hist*.txt histogramme.Rout histogramme.pdf

clean_collis: 
	rm collisions.txt collision.Rout collision.pdf

clean:
	rm *.txt main *.Rout *.pdf

