// Copyright (c) 2015, The Regents of the University of California (Regents)
// See LICENSE.txt for license details

#include <iostream>

#include "benchmark.h"
#include "builder.h"
#include "command_line.h"
#include "graph.h"
#include "reader.h"
#include "writer.h"
#include "../msr.h"

using namespace std;

int main(int argc, char* argv[]) {
  int cpu_info[3];
  double energy_units[2];
  get_cpu_info(CPU_HASWELL_EP, cpu_info, energy_units);  

  CLConvert cli(argc, argv, "converter");
  cli.ParseArgs();

  int fd = open_msr(0);  
  long long result; 
  double package_before, package_after;
  result = read_msr(fd, MSR_PKG_ENERGY_STATUS);
  package_before = (double) result*energy_units[0];
  close(fd);

  if (cli.out_weighted()) {
    WeightedBuilder bw(cli);
    WGraph wg = bw.MakeGraph();
    wg.PrintStats();
    WeightedWriter ww(wg);
    ww.WriteGraph(cli.out_filename(), cli.out_sg());
  } else {
    Builder b(cli);
    Graph g = b.MakeGraph();
    g.PrintStats();
    Writer w(g);
    w.WriteGraph(cli.out_filename(), cli.out_sg());
  }

  fd = open_msr(0);
  result = read_msr(fd, MSR_PKG_ENERGY_STATUS);
  package_after = (double)result*energy_units[0];
  fprintf(stderr, "********* converter *********\n");
  fprintf(stderr,"energy consumed: %fJ\n", package_after - package_before);

  return 0;
}
