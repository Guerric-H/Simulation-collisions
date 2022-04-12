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

standard: clean_stand compile
	./main standard
	R CMD BATCH standard.R

confiance: clean_conf compile 
	./main confiance
	R CMD BATCH confiance.R

histogramme: clean_histo compile
	./main histogramme
	R CMD BATCH histogramme.R


collision: clean_collis compile
	./main collision
	R CMD BATCH collision.R
	R CMD BATCH e2_90succes.R

clean_stand: 
	rm -f standard.txt standard.Rout standard.pdf

clean_conf: 
	rm -f confiance.txt confiance.Rout confiance.pdf

clean_histo: 
	rm -f hist*.txt histogramme.Rout histogramme.pdf

clean_collis: 
	rm -f collisions.txt collision.Rout e2_90succes.Rout e2_90succes.pdf collision.pdf 

clean : 
	rm -f *.txt main *.Rout 

clean_w_pdf:
	rm -f *.txt main *.Rout *.pdf

