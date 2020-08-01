
flag = -std=c++11

gsort: tree.h tree.cpp main.cpp LinkDict.cpp
		g++ $(shell root-config --libs --cflags) $(flag) $^ -o $@

LinkDict.cpp : gsang.h tree.h Linkdef.h
	    #root 6
		#rootcling -f LinkDict.cpp -c $^
		# root 5
		rootcint -f LinkDict.cpp -c $^

clean:
	rm -rf gsort *Dict*
