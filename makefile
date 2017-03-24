all:
	g++  `pkg-config --cflags poppler-qt5 poppler-cpp Qt5Core Qt5Gui` `pkg-config --libs poppler-qt5 poppler-cpp Qt5Core Qt5Gui Qt5Widgets` -fPIC cutter.cpp
