sim:     play.cpp  manip_time.o
	g++ play.cpp link.hpp manip_time.o -o run

manip_time.o: manip_time.cpp manip_time.hpp
	g++ -c manip_time.cpp manip_time.hpp

link: link.hpp
	g++ link.hpp
