CCFLAGS = 	$(shell perl -MExtUtils::Embed -e ccopts) -I/home/charles/perl5/perlbrew/perls/perl-5.34.0/lib/5.34.0/x86_64-linux/CORE
LDFLAGS = 	$(shell perl -MExtUtils::Embed -e ldopts) -L/home/charles/perl5/perlbrew/perls/perl-5.34.0/lib/5.34.0/x86_64-linux/CORE

.cpp.o:
	g++ -c $< $(CCFLAGS)

pdfm: perlFunction.o main.o
	g++ perlFunction.o main.o -o pdfm $(LDFLAGS)
	
all: pdfm

clean:
	rm -rf *.o pdfm