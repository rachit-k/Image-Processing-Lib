MKLFLAGS =  -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl

OPENBLASFLAGS = /opt/OpenBLAS-develop/libopenblas.a

output: main.o activation.o subsampling.o probability.o lenetconv.o wpwm.o wpwom.o wopwm.o wopwom.o pthmult.o mklib.o openblaslib.o
	g++ main.o activation.o subsampling.o probability.o lenetconv.o wpwm.o wpwom.o wopwm.o wopwom.o pthmult.o mklib.o openblaslib.o -o output ${MKLFLAGS} ${OPENBLASFLAGS} 

main.o: main.cpp activation.cpp subsampling.cpp probability.cpp lenetconv.cpp wpwm.cpp wpwom.cpp wopwm.cpp wopwom.cpp pthmult.cpp mklib.cpp openblaslib.cpp activation.h subsampling.h probability.h lenetconv.h wpwm.h wpwom.h wopwm.h wopwom.h pthmult.h mklib.h openblaslib.h 
	g++ -c main.cpp

activation.o: activation.cpp activation.h
	g++ -c activation.cpp

subsampling.o: subsampling.cpp subsampling.h
	g++ -c subsampling.cpp

probability.o: probability.cpp	probability.h
	g++ -c probability.cpp

wpwm.o: wpwm.cpp wpwm.h
	g++	-c wpwm.cpp

wpwom.o: wpwom.cpp wpwom.h
	g++ -c wpwom.cpp

wopwm.o: wopwm.cpp wopwm.h
	g++ -c wopwm.cpp

wopwom.o: wopwom.cpp wopwom.h
	g++ -c wopwom.cpp	

lenetconv.o: lenetconv.cpp lenetconv.h
	g++ -c lenetconv.cpp

pthmult.o: pthmult.cpp pthmult.h
	g++ -c pthmult.cpp			

mklib.o: mklib.cpp mklib.h
	g++  -c mklib.cpp 

openblaslib.o: openblaslib.cpp openblaslib.h
	g++ -c openblaslib.cpp

clean:
	rm *.o output
