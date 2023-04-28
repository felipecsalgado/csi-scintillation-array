//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("testem3")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  // Tuple
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);   // enable inactivation of histograms

  // Define histograms start values
  
  const G4String id[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "10","11","12","13","14","15","16","17","18","19",
                         "20","21","22","23","24","25","26","27","28","29",
                         "20","21","22","23","24","25","26","27","28","29",
                         "30","31","32","33","34","35","36","37","38","39",
                         "40","41","42","43","44","45","46","47","48","49",
                         "50","51","52","53","54","55","56","57","58","59",
                         "60","61","62","63","64","65","66","67","68","69",
                         "70","71","72","73","74","75","76","77","78","79",
                         "80","81","82","83","84","85","86","87","88","89",
                         "90","91","92","93","94","95","96","97","98","99",
                         "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "10","11","12","13","14","15","16","17","18","19",
                         "20","21","22","23","24","25","26","27","28","29",
                         "20","21","22","23","24","25","26","27","28","29",
                         "30","31","32","33","34","35","36","37","38","39",
                         "40","41","42","43","44","45","46","47","48","49",
                         "50","51","52","53","54","55","56","57","58","59",
                         "60","61","62","63","64","65","66","67","68","69",
                         "70","71","72","73","74","75","76","77","78","79",
                         "80","81","82","83","84","85","86","87","88","89",
                         "90","91","92","93","94","95","96","97","98","99",      
                         "100","101","102"};
  G4String title;

  // Default values (to be reset via /analysis/h1/set command)
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;
  
  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    if (k < kMaxAbsor) title = "Edep in absorber " + id[k];
    if (k > kMaxAbsor) title = "Edep longit. profile (MeV/event) in absorber "
                               + id[k-kMaxAbsor];
    if (k == 2*kMaxAbsor+1) title = "energy flow (MeV/event)";
    if (k == 2*kMaxAbsor+2) title = "lateral energy leak (MeV/event)";
    G4int ih = analysisManager->CreateH1(id[k], title, nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, true);
  }

  //***************************//
  //******** Create nTuples *******//
  //analysisManager->CreateNtuple("GeminiGamma", "Plane1 at 1x1cm2");
  analysisManager->SetFirstNtupleId(1);
  //id 1
  analysisManager->CreateNtuple("GammaSpectrum", "Hits");
  analysisManager->CreateNtupleDColumn("ypos"); // column Id = 0
  analysisManager->CreateNtupleDColumn("zpos"); // column Id = 1
  analysisManager->CreateNtupleDColumn("px"); // column Id = 2
  analysisManager->CreateNtupleDColumn("py"); // column Id = 2
  analysisManager->CreateNtupleDColumn("pz"); // column Id = 2
  analysisManager->CreateNtupleDColumn("energy"); // column Id = 2
  analysisManager->CreateNtupleDColumn("idpart"); // column Id = 2
  analysisManager->FinishNtuple();


}
