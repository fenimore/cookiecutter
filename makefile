all:
	g++ cutter.cpp `pkg-config --cflags poppler-qt4 QtCore poppler-cpp` `pkg-config --libs poppler-cpp poppler-qt4`
