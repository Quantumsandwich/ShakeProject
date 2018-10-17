#MakeFile to build and deploy the Shakespeare Program Data using ajax
#By Benjamin Gross
#Modified from code provided in class by prof. Skon.

# Put your user name below:
USER=gross3

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: namelookup PutCGI PutHTML

shake.o: shake.cpp shake.h english_stem.h
	$(CC) $(CFLAGS) shake.cpp -c

namelookup.o: namelookup.cpp shake.h english_stem.h
	$(CC) -c $(CFLAGS) namelookup.cpp 

namelookup: namelookup.o shake.o
	$(CC) namelookup.o -o namelookup shake.o -L/usr/local/lib -lcgicc 

PutCGI: namelookup
	chmod 757 namelookup
	cp namelookup /usr/lib/cgi-bin/$(USER)_namelookup.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp namelookup.html /var/www/html/class/softdev/$(USER)/Names/
	cp namelookup.css /var/www/html/class/softdev/$(USER)/Names/
	cp namelookup.js /var/www/html/class/softdev/$(USER)/Names/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/Names/
clean:
	rm -f *.o  namelookup
