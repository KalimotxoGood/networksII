sim:     2play.cpp  manip_time.o
	g++ 2play.cpp link.hpp router.hpp manip_time.o -o run

manip_time.o: manip_time.cpp manip_time.hpp
	g++ -c manip_time.cpp manip_time.hpp

link: link.hpp
	g++ link.hpp

router: router.hpp
	g++ 
