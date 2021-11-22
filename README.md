# Instructions 
To run, install papi: http://icl.utk.edu/papi/software/
Each file should have compilation instructions in it. 

# General 
The papi-code folder contains sample code that papi folks provided to show how
to use the framework. If you get weird errors with the tests folder, it would be
nice to validate that the files in papi-code work. 

#Common Errors
1. Can't find shared library
    - if you get that error in non-sudo mode, you should update you
      LD_LIBRARY_PATH variable to reflect wherever the lib files are compiled to
      in your system (very often, this is in /usr/local/lib)
    - if this happens in sudo mode despite updating LD_LIBRARY_PATH, use the
      following command instead:
        sudo LD_LIBRARY_PATH=`location of lib` <executable>

2. Component containing event is disabled/ Component index isn't set 
    - you need to provide permissions to your code to read certain counters. use
      the following command:
        echo 0 > /proc/sys/kernel/perf_event_paranoid
