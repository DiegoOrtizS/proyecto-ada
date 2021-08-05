all : miniprolog dptries

miniprolog: 
	g++ miniprolog.cpp -o miniprolog.out

dptries:
	g++ dptries.cpp -o dptries.out

clean:
	rm -rf *.out