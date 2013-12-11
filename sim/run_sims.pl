#!/usr/bin/perl

# define array of trace names we want to run
#@traces = ("ammp","applu","bwaves","bzip2","equake","facrec","galgel","gap","gcc","hmmer","mcf","mesa","mgrid","parser","sixtrack","soplex","swim","vortex","vpr","wupwise");
@traces = ("sample");

# define number of prefetchers
$numPrefetchers = 30;

# for each trace
foreach $trace (@traces){
	# create results dir
	`mkdir results/$trace/`;
	# run each prefetcher
	for ($i = 0; $i < $numPrefetchers; $i++){
	
		# run the simulation
		print `./Simulator/Scripts/run_simulator.py --definition 1-core/stream --config lru/1m --folder scratch --trace-selector traces/ --workload $trace --warm-up 0 --run-time 250000000 --prefetcher $i`;

		# copy results to a specified trace folder
		`mkdir results/$trace/$i`;
		`mv scratch/1-core/stream/lru/1m/$trace/* results/$trace/$i/`;

	}
}
