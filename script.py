#!/bin/python

import os 

# each of the 4 functions
for f in [1, 2, 3, 4]:
	# different array sizes
	for n in [1000, 50000, 100000, 500000, 1000000, 4000000, 8000000, 16000000, 32000000]:
		# how many runs to get an average
		avgRuns = 10;
		

		cmd = "g++ -DFUNCTION=%d -DNUMS=%d -DAVGRUNS=%d proj5.cpp simd.p5.cpp -o proj5 -lm -fopenmp" % (f, n, avgRuns)
		os.system(cmd)
		cmd = "./proj5 >> output.txt"
		os.system(cmd)
	