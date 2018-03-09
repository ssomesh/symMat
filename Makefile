main: driver.cpp symmat.h
	g++ driver.cpp -o symMat -std=c++11

clean:
	rm -f symMat
