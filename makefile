sim:     main.cpp
	g++ main.cpp link.hpp router.hpp sourceDestinationPairs.hpp packet.hpp manip_time.o -o run

manip_time.o: manip_time.cpp manip_time.hpp
	g++ -c manip_time.cpp manip_time.hpp

link: link.hpp
	g++ link.hpp

router: router.hpp
	g++ 

sourceDestinationPairs: sourceDestinationPairs.hpp
	g++ sourceDestinationPairs.hpp

packet: packet.hpp
	g++ packet.hpp
