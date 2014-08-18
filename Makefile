all: hop hop_graph sha1_find

hop: hop.cc
	$(CXX) -std=gnu++11 -o $@ $< -g -fPIC -pie

hop_graph: hop_graph.cc
	$(CXX) -std=gnu++11 -o $@ $< -g -fPIC -pie -O2

sha1_find: sha1_find.cc
	$(CXX) -std=gnu++11 -o $@ $< -g -fPIC -pie -O2 -lcrypto


