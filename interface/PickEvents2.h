//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 22 10:39:08 2020 by ROOT version 6.20/08
// from TTree tree/Event Summary
// found on file: UnprefirableEventList_SingleMuon_Run2017BtoF.root
//////////////////////////////////////////////////////////

#ifndef PickEvents2_h
#define PickEvents2_h

#include <TROOT.h>
#include <TChain.h>
#include <vector>
#include <map>
#include <assert.h>
#include <TFile.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.

class PickEvents2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        event;
   Long64_t        run;
   //Long64_t        lumi;
   //Int_t           nvtx;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   //TBranch        *b_lumi;   //!
   //TBranch        *b_nvtx;   //!

   PickEvents2(TTree *tree=0);
   virtual ~PickEvents2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual std::map<Long64_t, std::vector<Long64_t>>     Loop();
   virtual void Loop();
// virtual bool bsearch(std::vector<Long64_t> &v, Long64_t value); 
 virtual Bool_t   Notify();
 
   virtual void     Show(Long64_t entry = -1);
   virtual bool match(Long64_t sample_run, Long64_t sample_event);
   bool first;
};

#endif

#ifdef PickEvents2_cxx
PickEvents2::PickEvents2(TTree *tree) : fChain(0), first(true) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("JetMETStudies/JMEAnalyzer/python/UnprefirableEventList_SingleMuon_Run2017BtoF.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("UnprefirableEventList_SingleMuon_Run2017BtoF.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

PickEvents2::~PickEvents2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PickEvents2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PickEvents2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PickEvents2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   //fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   //fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   Notify();
}

Bool_t PickEvents2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PickEvents2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PickEvents2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PickEvents2_cxx
