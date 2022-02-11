#define PickEvents2_cxx
#include "JetMETStudies/JMEAnalyzer/interface/PickEvents2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <map>
#include <vector>
#include <assert.h>
#include <TMath.h>
#include <iostream>
//using namespace std;

std::vector<Long64_t> list_runs; 
//... so we want to group the first 4 events with the same run
std::vector<Long64_t> list_events;

std::map<Long64_t, std::vector<Long64_t>> run_to_event_map;

void PickEvents2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L PickEvents2.C
//      root> PickEvents2 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (! first ) return;
   if (fChain == 0) return;
   first = false;

   Long64_t nentries = fChain->GetEntriesFast();
   list_runs.clear();
   list_events.clear();
   run_to_event_map.clear();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry < nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      //list_runs.push_back(run);
      //list_events.push_back(event);
      // std::cout << "run: " << run << endl;
      assert(list_runs.size() == list_events.size() );
      if (run_to_event_map.find(run) == run_to_event_map.end() ) {
	run_to_event_map[run] = std::vector<Long64_t>();
      }
      run_to_event_map[run].push_back(event);
   }



   //}
   //cout << list_runs << endl;
   //put the preprocess in loop
   //run_to_event_map.clear();
   //assert(list_runs.size() == list_events.size() );
   //for (Int_t i=0; i < (Int_t) list_runs.size(); i++) {
     //Long64_t run_i = list_runs[i];
      //Long64_t event_i = list_events[i];
      //if (run_to_event_map.find(run_i) == run_to_event_map.end() ) {
	//run_to_event_map[run_i] = std::vector<Long64_t>();
	 //}
      //run_to_event_map[run_i].push_back(event_i);
      //}
   for (auto &it : run_to_event_map) {
     sort(it.second.begin(), it.second.end());
   }
}

// bool PickEvents2::bsearch(std::vector<Long64_t> &v, Long64_t value) {
//    Int_t start = 0;
//    v.clear();
//    Int_t  end = v.size() -1;
//    while (start <= end) {
//       Int_t mid = (start + end) / 2;
//       if (v[mid] > value) {
//          end = mid - 1;
//       } else if (v[mid] < value) {
//          start = mid + 1;
//       } else {
//          return true;
//       }
//    }
//    return false;
// }


bool PickEvents2::match(Long64_t sample_run, Long64_t sample_event) {
  PickEvents2::Loop();
   //PickEvents2::bsearch(std::vector<Long64_t> &v, Int_t value);
   if (run_to_event_map.find(sample_run) == run_to_event_map.end() ) {
      return false;
   }
   //return PickEvents2::bsearch(run_to_event_map[sample_run], sample_event);
   auto N = run_to_event_map[sample_run].size();
   std::vector<Long64_t> vec = run_to_event_map[sample_run];
   // sort (vec.begin(), vec.end());
   //Long64_t arr[N] = &vec[0];
   auto J = TMath::BinarySearch(N , vec.data(), sample_event);
   bool found = vec[J] == sample_event;
   if ( found ) return true;
   return false;
}
//test on match(297292, 840021146)   //true  match(297292, 839822512)
//match(297292, 840044967) 

//        row         event *       run *      lumi *      nvtx *
// ************************************************************
// *        0 * 840044967 *    297292 *       465 *        19 *
// *        1 * 840021146 *    297292 *       465 *        24 *
// *        2 * 839272244 *    297292 *       465 *        32 *
// *        3 * 839833613 *    297292 *       465 *        29 *
// *        4 * 839822512 *    297292 *       465 *        24 *
// *        5 * 839143851 *    297292 *       465 *        25 *
// *        6 * 839214832 *    297292 *       465 *        13 *

