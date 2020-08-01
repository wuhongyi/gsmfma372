#include "tree.h"
#include <iostream>
#include <cstdlib>
#include "TString.h"

int main(int argc, char *argv[])
{

  if(argc < 2)
    {
      std::cout<< "eg. ./xxx  [run number]" <<std::endl;
      exit(1);
    }
  
  int N = atoi(argv[1]);
  

  auto ipf = new TFile(TString::Format("/data/d2/gsmfma372/rootdata/run%d.root",N),"READ");
  auto ipt = (TTree*)ipf->Get("opt");

  auto opf = new TFile(TString::Format("data%d.root",N),"RECREATE");
  auto opt = new TTree("opt","opt");

  auto it = new tree(ipt);
  it->Loop(opt);


  opt->Write();
  opf->Close();
  
  return 0;
}


