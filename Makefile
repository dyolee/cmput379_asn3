hash:
	gcc -std=c99 -Wall hashtable.c -o hashtable
sim:
	gcc -std=c99 -Wall simulator.c -o sim
clean:
	rm -rf hashtable sim *.csv
run: 
	./sim

	
