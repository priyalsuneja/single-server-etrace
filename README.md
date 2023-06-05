Introduction 
------------
This is a project to measure the energy consumed by applications with the help
of Hardware Performance Counters.
The folders have the following content:
1. gapbs: Contains the modified gapbs benchmark including energy measurement
          for the files. 
2. papi-code: Contains sample code to use the PAPI library (which was used in
              the earlier versions of this project, but then abandoned). It also
              contains sample code to access model specific registers to read
              power info on a processor that supports Intel RAPL. 
3. test/msr: This folder contains all the necessary code for my CSE 550 project.
             It has tests that allow measuring the hardware performance counters
             mentioned in my writeup, and enable calculating how much energy
             they consumed per unit event. 
4. test/rapl: This folder contains similar (but perhaps outdated) tests to
              test/msr, only, it uses the PAPI library to access HPCs instead of
              perf. 
5. test/temp: This folder contains files and tests that are still in progress at
              the time of submission of the project. This includes, but isn't
              limited to code to measure branch mispredictions, l3 cache misses
              and fp instructions.

Instructions 
------------
- The code that you would want to run is in the test/msr folder. To build it,
  simply run `make` in that directory. This should result in compiled binaries
  in the test/msr/build folder. 
- For each file, you need to run it with sudo. For eg: sudo ./build/ins_msr (if
  being run from single-server-etrace/test/msr).
- In order to measure energy values, you will have to run this code on a machine
  with HASWELL_EP architecture (I'm sorry, I didn't have the time to make the
  code portable!). This architecture is available on the syslab servers,
  specifically on anteater. 
- When using perf, we care about the following events:
  * l2_rqsts.miss
  * dTLB-load-misses
  * L1-dcache-load-misses
  * instructions

  To run perf to get a performance counter value, use the following command
  (this is for measuring L1 cache misses only)

  sudo perf stat -e L1-dcache-load-misses `path to folder`/single-server-etrace/tests/msr/build/l1_msr

  This will output two numbers - the number of l1 cache misses and the total
  energy consumed by l1_msr in joules. On dividing this, you get the energy
  spent per L1 cache miss!

- To run the GAP BS code, you need to first build it. 
    After going to the gapbs folder, type in make. This will result in binaries
    being created in the gapbs folder.
    
    To measure the energy and HPCs for gapbs, go to the gapbs folder and run:
    sudo perf stat -e l2_rqsts.miss -e dTLB-load-misses -e L1-dcache-load-misses -e instructions sssp -g 20 -n 1
        
     where sssp is one of the 8 benchmarks provided by gapbs

     This will print 5 numbers to stderr: the energy consumption of the
     process, #l2 misses, #l1 misses, #tlb misses and total number of
     instructions. 

    We used this information to then create an energy consumption prediction for
    the application. 
    
Common Errors
-------------
1. Can't find shared library
    - if you get that error in non-sudo mode, you should update you
      LD_LIBRARY_PATH variable to reflect wherever the lib files are compiled to
      in your system (very often, this is in /usr/local/lib)
    - if this happens in sudo mode despite updating LD_LIBRARY_PATH, use the
      following command instead:
        sudo LD_LIBRARY_PATH=`location of lib` ./`executable`

2. Component containing event is disabled/ Component index isn't set 
    - you need to provide permissions to your code to read certain counters. use
      the following command:
        echo 0 > /proc/sys/kernel/perf_event_paranoid

3. Can't isntall perf for the given kernel using linux-tools-generic
    - this can happen for certain kernel versions. if this is the case, download
      linux's source code from github, go to linux/tools/perf and run "make". 
    - once make finished, do: "cp perf /usr/bin"
    * note that to make perf, you will need flex and bison. 

Setups & Installations:
-------------
1. Basics:
    - check the machine you want to run EPerf on is intel machine that contains the needed hardware counters
    - make sure rapl is working
      wget https://web.eece.maine.edu/~vweaver/projects/rapl/rapl-read.c 
      gcc -O2 -Wall -o rapl-read rapl-read.c -lm
      sudo ./rapl-read 
    - sudo modprobe msr
    - install perf from source
      git clone https://github.com/torvalds/linux.git
      cd linux/tools/perf
      make
      sudo cp perf /usr/bin
    - other basic installations
      sudo apt-get install linux-tools-common linux-tools-generic
      (might need to add kernal version 
       e.g. sudo apt-get install linux-tools-5.4.0-139-generic linux-cloud-tools-5.4.0-139-generic)

2. Python:
    - sudo apt-get update
    - sudo apt-get install python3
    - sudo apt-get install python3-pip
    - sudo pip install cvxpy
    - sudo pip install matplotlib

3. Running:
    - update the labels with correct path for benchmarks and files in /scripts/run_perf.sh
    - sudo ./scripts/run_perf.sh
    - (sudo rm -rf data/data/bc_out_data if there is such file being generated)
    - sudo ./scripts/calc.sh
    - see results in temp_output folder
    - if any benchmark is not working, rerun make in its directory.
    - if changes are made in any source files, rerun make for the "fifth" executable 


     

