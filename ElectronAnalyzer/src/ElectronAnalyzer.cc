// -*- C++ -*-
//
// Package:    ElectronAnalyzer
// Class:      ElectronAnalyzer
// 
/**\class ElectronAnalyzer ElectronAnalyzer.cc LongLivedNeutralParticlesAnalysis/ElectronAnalyzer/src/ElectronAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Thu Feb 22 02:00:06 CLST 2018
// $Id$
//
//

// system include files
#include<vector>
#include<TLorentzVector.h>
#include<cmath>
#include <memory>
#include <Math/GenVector/PxPyPzE4D.h>                                                                                                   
#include <Math/GenVector/PxPyPzM4D.h>
#include "vector"
#include "algorithm"
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include "DataFormats/TrackReco/interface/TrackFwd.h"
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "HLTrigger/HLTcore/interface/HLTConfigData.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

//
// class declaration
//

class ElectronAnalyzer : public edm::EDAnalyzer {
   public:
      explicit ElectronAnalyzer(const edm::ParameterSet&);
      ~ElectronAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      
     bool cmsStandardCuts(const edm::Event&, const edm::EventSetup&);
     bool matchingCuts( bool , double , int , int , double, double, double);
     double deltaR(double , double , double, double);
     double conePt(int , int , double , double , int ,const edm::Event& , const edm::EventSetup& );
     double mCos(double , double , double , double  );
     double mTheta(double , double , double , double );
     double invMass(double , double , double , double  , double ,  double );
     double dotProduct(double , double , double , double );
     bool impactParameterCut(reco::TrackCollection::const_iterator, reco::TrackCollection::const_iterator, reco::BeamSpot );
  
      TFile * mfile;   
      TH1F * h_invMass;
      TH1F * h_invMassLoose;
      TH1F * h_lxy_err;
      TH1F * h_lxy;
      TH1F * nEvents;
     
	  HLTConfigProvider hltConfig_;

      // ----------member data ---------------------------
     
      std::string   processName_;
      std::string   triggerName_;
      std::string   datasetName_;
      edm::InputTag triggerResultsTag_;
      edm::InputTag triggerEventTag_;
      edm::InputTag trackTags_; //used to select what tracks to read from configuration file
      std::string  outFile_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor  
//
ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& iConfig)
:
 
processName_(iConfig.getParameter<std::string>("processName")),
triggerName_(iConfig.getParameter<std::string>("triggerName")),
datasetName_(iConfig.getParameter<std::string>("datasetName")),
triggerResultsTag_(iConfig.getParameter<edm::InputTag>("triggerResults")),
triggerEventTag_(iConfig.getParameter<edm::InputTag>("triggerEvent")),
trackTags_(iConfig.getUntrackedParameter<edm::InputTag>("tracks")),
outFile_(iConfig.getParameter<std::string>("outFile"))
{
   //now do what ever initialization is needed

}


ElectronAnalyzer::~ElectronAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ElectronAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace std;


/***
 * Here the handlers for the various objects that will be
 * used in the analysis are initialized. These correspond to:
 * traks, triggers,trigger results, verteces and beamspot objects.
 * **/
Handle<TrackCollection> tracks;
Handle<edm::TriggerResults> trigResults; 
Handle<trigger::TriggerEvent> trigEvent; 
Handle<reco::VertexCollection> vertHand;
Handle<reco::BeamSpot> beamSpotHandle;
Handle<reco::TrackCollection> tks;
ESHandle<TransientTrackBuilder> theB;

edm::InputTag trigResultsTag("TriggerResults","","HLT");
edm::InputTag trigEventTag("hltTriggerSummaryAOD","","HLT");

/*** Here the handlers are filled with the corresponding object
 * found in the AOD files
 * **/

iEvent.getByLabel(trackTags_,tracks);
iEvent.getByLabel(trigResultsTag,trigResults);
iEvent.getByLabel(trigEventTag,trigEvent);
iEvent.getByLabel( "offlinePrimaryVertices",vertHand);
iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
iEvent.getByLabel(trackTags_, tks);

const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);

nEvents->Fill(1); //The total number of events will be used to normalize histograms.

// get primary vertex coordinates
bool primaryVertexFound = false;
double vertex_x=0, vertex_y=0, vertex_xError=0, vertex_yError=0;
 for(reco::VertexCollection::const_iterator itVert = vertHand->begin();
       itVert != vertHand->begin()+1&& itVert != vertHand->end();
       ++itVert)
       {
		   vertex_x=itVert->x();
		   vertex_y = itVert->y();
		   vertex_xError=itVert->xError();
		   vertex_yError=itVert->yError();
			 
	   }
 reco::BeamSpot beamSpot;
// get beamspot coordinates
double beamX = 0;
double beamY = 0;
double beamXErr = 0;
double beamYErr = 0;
if ( beamSpotHandle.isValid() )
{
    beamSpot = *beamSpotHandle; 
    beamX = beamSpot.x0();
    beamY = beamSpot.y0();
    beamXErr = beamSpot.x0Error();
    beamYErr = beamSpot.y0Error();
    if(beamX && beamY && beamXErr && beamYErr){}
}
 
 
std::string pathName = "none";


std::string toFind[4] = {"HLT_DoublePhoton33_v","HLT_DoublePhoton33_HEVT", "HLT_DoublePhoton38_HEVT"};
/*** Photon AOD files (used for the electron analysis part) may have any of the above triggers
 * and may also differ from file to file. In the loop below we check which one it is.
 * **/

int trigPathSize = trigNames.size();
int triggerFound=9999;
for(int j = 0; j < 4; j++){
for (unsigned int i = 0; i< trigNames.size(); i++)
{
	
	
	std::string trig = trigNames.triggerName(i);
	if ( trig.find(toFind[j]) !=std::string::npos ){
		
		
		triggerFound=j;
		pathName = trig;
		i = trigNames.size();
		j = 4;
		
		}
		
	}
}
/*** Here we check if the trigger was activated and store the result
 * in the variable passTrig. This is a requirement for the analysis.
 * ***/
bool passTrig;
int trigIndex = trigNames.triggerIndex(pathName);
if (trigIndex != trigPathSize && primaryVertexFound)
{
    passTrig=trigResults->accept(trigNames.triggerIndex(pathName));   // may cause vector::_M_range_check exeption
    
}
else
{
	passTrig=false;
}
int prescale = hltConfig_.prescaleValue(iEvent,iSetup,pathName) ;

// find lowest trigger prescale from  of all activated triggers. Will be used for weighting
for (unsigned int i = 0; i< trigNames.size(); i++)
{
	std::string trig = trigNames.triggerName(i);
	
	if (trigResults->accept(trigNames.triggerIndex(trig)))
	{
		if (prescale > (int)hltConfig_.prescaleValue(iEvent,iSetup,trig))
		{
			prescale = hltConfig_.prescaleValue(iEvent,iSetup,trig);
		}
	}
}



/*** A trigger is composed of several ordered filters (can be thought of as sub triggers).
 * If the last filter was activated that means the trigger was activated. Here the filter
 * corresponding to the trigger found in the file is stored as a string in the variable filterName.
 * It will be used later on to initialize a trigger object that will contain the information about
 * the physical object that activated the trigger
 * **/

std::string filterName = "none";

if (triggerFound == 0)
{
	filterName = "hltDoublePhoton33EgammaLHEDoubleFilter";
}
else if (triggerFound == 1)
{
	filterName = "hltDoubleEG33HEVTDoubleFilter";
}
else 
{
	filterName = "hltDoubleEG38HEVTDoubleFilter";
}



 
bool standardCuts = cmsStandardCuts(iEvent, iSetup); //cmsStandardCuts() definition at line 525

/** the variable matchedTrack contains the 1s or 0s at the 
 * position corresponding to the index of a track that either
 * matched with a trigger or not correspondigly. Below the variabe
 * is reset into a vector of 0s.
 * **/
int matchedTrack[tracks->size()];
for (int i = 0; i<(int)tracks->size(); i++)
{
	matchedTrack[i] = 0;
}

std::string e_filterName(filterName);
trigger::size_type e_filterIndex = trigEvent->filterIndex(edm::InputTag(e_filterName,"",trigEventTag.process())); 
  
 if(e_filterIndex<trigEvent->sizeFilters())
 { 
      const trigger::Keys& trigKeys = trigEvent->filterKeys(e_filterIndex);  
      const trigger::TriggerObjectCollection & e_trigObjColl(trigEvent->getObjects());


/** the analysis section of the code begins. First we check that the 
 * standardCuts requirements are satisfied, that the double photon 
 * trigger was activated and that a valid beamspot object was created
 * int the event.
 * **/     
if ((standardCuts && passTrig && beamSpotHandle.isValid()) )
{
 int i = 0;
 for(TrackCollection::const_iterator itTrack = tracks->begin();
       itTrack != tracks->end();                      
       ++itTrack) 
       {
		  for(trigger::Keys::const_iterator keyIt=trigKeys.begin();keyIt!=trigKeys.end();++keyIt)
		  {
			   const trigger::TriggerObject& obj = e_trigObjColl[*keyIt];
			 
			   bool lepMatchCut =matchingCuts( itTrack->quality(reco::Track::highPurity)  , itTrack->pt() , itTrack->hitPattern().numberOfValidTrackerHits(),itTrack->hitPattern().numberOfValidPixelHits(), itTrack->eta(), itTrack->dxy(beamSpot), itTrack->dxyError());
		
		  
		   if (lepMatchCut)
		   { 
			    if(deltaR(itTrack->phi(), itTrack->eta(), obj.phi(), obj.eta())< 0.1 )
			   {  
				   matchedTrack[i] = 1;     
			   }
			   
		   } 
			  
		  }
		  i++;
	   }
}
}



int  i =0;
for(TrackCollection::const_iterator itTrack1 = tracks->begin();
       itTrack1 != tracks->end();                      
       ++itTrack1) 
{
	if (itTrack1->charge()==1 && matchedTrack[i] == 1 ){
	int	j=0;
	for(TrackCollection::const_iterator itTrack2 = tracks->begin();
       itTrack2 != tracks->end();                      
       ++itTrack2) 
       {
		   if(itTrack2->charge() ==-1 && matchedTrack[j] ==1    )
		   {  
			   
 // Secondary vertex is reconstructed
			   // get RECO tracks from the event
					
					
                    KalmanVertexFitter fitter;
					//get the builder:
					
					iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
					//do the conversion:
					std::vector<reco::TransientTrack> t_tks = (*theB).build(tks);
					
				   
				   std::vector<reco::TransientTrack> trackVec;
                    
				   if ( (int)t_tks.size()>2){

				   trackVec.push_back(t_tks[i]);
					

				   trackVec.push_back(t_tks[j]); 
				   TransientVertex myVertex = fitter.vertex(trackVec);
				  
		 
				  
              if (myVertex.isValid() && myVertex.normalisedChiSquared() < 5)
					 {
			    double secVert_x =(double)myVertex.position().x();
			    double secVert_y =(double)myVertex.position().y();
			    double conePt_var=conePt(i , j, itTrack1->eta(), itTrack1->phi(),  tracks->size(), iEvent,iSetup);
			    //double cosAlpha = mCos(itTrack1->phi(), itTrack1->eta(), itTrack2->phi(), itTrack2->eta());
			    double theta = mTheta(itTrack1->px()+itTrack2->px(), itTrack1->py()+itTrack2->py(),secVert_x -vertex_x,  secVert_y-vertex_y);
			    bool IPC = impactParameterCut(itTrack1, itTrack2, beamSpot);
			    double secVertErrx = myVertex.positionError().cxx();
			    double secVertErry = myVertex.positionError().cyy();
				double tdl_x = secVert_x - vertex_x;
				double tdl_y = secVert_y - vertex_y;
				double tdl = sqrt(tdl_x*tdl_x + tdl_y*tdl_y);
				double tdl_errx = secVertErrx + vertex_xError;
				double tdl_erry = secVertErry + vertex_yError;
				//double tdl_err = sqrt(tdl_errx*tdl_errx + tdl_erry*tdl_erry);
				double difx = (secVert_x)/(sqrt((secVert_x*secVert_x)+(secVert_y*secVert_y)));
				double dify = (secVert_y)/(sqrt((secVert_x*secVert_x)+(secVert_y*secVert_y)));
				double tot_variance = difx*difx*tdl_errx +dify*dify*tdl_erry; 
				double tdl_err = sqrt(tot_variance);
				double invariantMass;
	
			    invariantMass = invMass(itTrack1->px(), itTrack1->py(), itTrack1->pz(),itTrack2->px(), itTrack2->py(), itTrack2->pz());
			    h_invMassLoose->Fill(invariantMass);
			    
			    if ((conePt_var < 4  && (theta < 0.8 )))
					
					{
			    
				         h_invMass->Fill(invariantMass, prescale);
	 
				         double lxy_err = tdl/(tdl_err);
				         if (lxy_err > 20)
				         {
							 lxy_err = 19;
					     }
				         h_lxy_err->Fill(lxy_err, prescale);
				         
				    //with lifetime related cuts
				         if (IPC && tdl/tdl_err > 5)
				         {
							// h_invMass_LC->Fill(invariantMass, prescale);
						 }
						 
				    
				 }
				 if ((conePt_var < 4  && (theta >3.1514- 0.8 )))
					
					{
				
					   
				
					  
		    
				   }
			   
		   }
		   }
		   }
		
		j ++;   
	   }
   }
i++;
}



//   Compare mathced tracks to see if they originated from the same vertex




#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
//mtree->Fill();

}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronAnalyzer::beginJob()
{TH1::AddDirectory(true);

 const char* of = outFile_.c_str();
 mfile = new TFile(of, "recreate");
 
 h_invMass = new TH1F ("InvMass", "Lepton Pair Invariant Mass", 100, 0 , 600);
 h_invMassLoose = new TH1F ("InvMassLoose", "Lepton Pair Invariant Mass with no theta cut", 100, 0 , 600);
 h_lxy_err = new TH1F ("Lxy_err", "Transeverse decay length",20,0,20); 	  
 
 nEvents = new TH1F ("nEvents", "Number of Events", 5, -5,5);
		
}




           


          


// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronAnalyzer::endJob() {

//mtree->Write();
//std::cout<<"num traks "<<Ntracks<<" num vertTraks "<<NvertTracks<<std::endl;
mfile->Write();
mfile->Close();
}





bool
ElectronAnalyzer::cmsStandardCuts(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 bool ret = false;
 int disp = 0;
 int numHighPurity = 0;
 int numTracks = 0;

 double purityFrac = 0.0;
 using namespace edm;
 using namespace reco;
   Handle<reco::VertexCollection> vertHand;
   iEvent.getByLabel( "offlinePrimaryVertices",vertHand);
   
   Handle<TrackCollection> tracks;
   iEvent.getByLabel(trackTags_,tracks);
   
   for(reco::VertexCollection::const_iterator itVert = vertHand->begin();
       itVert != vertHand->begin()+1 && itVert != vertHand->end();
       ++itVert)
       {
		  
		    for(reco::Vertex::trackRef_iterator itTrack = itVert->tracks_begin();
       itTrack != itVert->tracks_end();
       ++itTrack)
           {
		        
		 double tx = (**itTrack).vx();
	     double ty = (**itTrack).vy();
		 double tz = (**itTrack).vz();
		 double tr = sqrt(tx*tx +ty*ty);
		 if ( (tr < 2 )&&(tz < 24) )
		 {
			 disp ++;
		 }
 
    	   }
		    
	   }
	 
	   
	   for(TrackCollection::const_iterator itTrack = tracks->begin();
       itTrack != tracks->end();                      
       ++itTrack) 
       {   
		  
		   numTracks ++;
		   
		   if (itTrack->quality(reco::Track::highPurity))
		   {
			   numHighPurity++;
		   }
		   
	   }
	   
	   purityFrac = (double)numHighPurity/numTracks;
	   if (numTracks<10)
	   {
		   purityFrac = 1;
	   }
	   
	   if(disp >=4 && purityFrac >= 0.25)
	   {
		   ret = true;
	   }
	   
	
	
	return ret;
	

}




bool 
ElectronAnalyzer::matchingCuts( bool purity, double pt, int hits, int hits3D, double eta, double dxy, double dxyError)
{
	bool ret = false;
	
	
		
	  if(purity && pt > 41 && hits >= 6   && eta < 2  && hits3D >1)
	  if(true)
	  
	  {
		  ret = true;

	  }	
	 
	  

	
	return ret;
}
double 
ElectronAnalyzer::deltaR(double obj1Phi, double obj1Eta, double obj2Phi, double obj2Eta)
{
	double dPhi = obj1Phi - obj2Phi;
	if (abs(dPhi)>3.1415/2)
	{
		dPhi =  3.1415 -dPhi;
	}
	double dEta = obj1Eta - obj2Eta;
	double dR = sqrt(dPhi*dPhi + dEta*dEta);
	return dR;
}
double 
ElectronAnalyzer::conePt(int forbiddenIndex1, int forbiddenIndex2, double eta, double phi, int numTracks,const edm::Event& iEvent, const edm::EventSetup& iSetup )
{  
	using namespace edm;
	using namespace reco;
    Handle<TrackCollection> tracks;
   iEvent.getByLabel(trackTags_,tracks);
    int i =0;
	double sumPt = 0.0;
	for(TrackCollection::const_iterator itTrack = tracks->begin();
       itTrack != tracks->end();                      
       ++itTrack) 
	{
		if(deltaR(phi, eta, itTrack->phi(), itTrack->eta()) < 0.3 && deltaR(phi, eta, itTrack->phi(), itTrack->eta()) > 0.03 && i != forbiddenIndex1 && i != forbiddenIndex2)
		{
			sumPt = itTrack->pt() +sumPt;
			i++;
		}
	}
	
	return sumPt;
}
double 
ElectronAnalyzer::mCos(double phi1, double eta1, double phi2, double eta2 )
{double cosAlpha = cos(eta1)*cos(phi1)*cos(eta2)*cos(phi2) + cos(eta1)*sin(phi1)*cos(eta2)*sin(phi2) + sin(eta1)*cos(eta2);
	
	return cosAlpha;
}
double 
ElectronAnalyzer::mTheta(double ax, double ay, double bx, double by)
{
	double cosAlpha = ax*bx + ay*by;
	double theta;
	cosAlpha = cosAlpha/(sqrt(ax*ax+ay*ay)*sqrt(bx*bx+by*by));
	//std::cout<<"cosAlpha: "<<cosAlpha<<std::endl;
	theta  = acos(cosAlpha);
	if (theta > 3.1514)
	{
		theta =  2*3.1514-theta;
	}
	return theta;
}
double 
ElectronAnalyzer::invMass(double px1, double py1, double pz1, double px2 , double py2,  double pz2)
{
  double E1 =  sqrt(px1*px1 + py1*py1 + pz1*pz1);  // asummes rest mass energy to be negligible
  double E2 =  sqrt(px2*px2 + py2*py2 + pz2*pz2);
  
  double E = E1+E2;
  double px = px1 + px2;
  double py = py1 + py2;
  double pz = pz1 + pz2;
  double mass = sqrt(E*E - px*px - py*py - pz*pz);
  
  return mass;
  
  

	
}
double
ElectronAnalyzer::dotProduct(double x1, double y1 , double x2, double y2)
{
	double ret;
	ret = x1*x2+y1*y2;
	return ret;
}
bool
ElectronAnalyzer::impactParameterCut(reco::TrackCollection::const_iterator it1, reco::TrackCollection::const_iterator it2, reco::BeamSpot beamSpot)
{    
	double dxy1, dxy1Err, dxy2, dxy2Err, sig1, sig2;
	bool ret = false;
	dxy1 = it1->dxy(beamSpot);
	dxy2 = it2->dxy(beamSpot);
	dxy1Err = it1->dxyError();
	dxy2Err = it2->dxyError();
	
	sig1 = dxy1/dxy1Err;
	sig2 = dxy2/dxy2Err;
	
	if (sig1 > 2 && sig2 > 2)
	{
		ret = true;
	}
	
	
	return ret;
}
// -----------
// ------------ method called when starting to processes a run  ------------
void 
ElectronAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{ bool changed = true;
	if (hltConfig_.init(iRun,iSetup,processName_,changed)) {
    if (changed) {
		//hltConfig_.dump("Triggers");
		//std::cout<<"prescale table"<<std::endl;
		//hltConfig_.dump("PrescaleTable");
		//std::cout<<"	Molude Labels	"<<std::endl;
//		for (unsigned int i = 0; i < hltConfig_.moduleLabels("HLT_DoublePhoton33_v2").size(); i++){   //  for data
		//for (unsigned int i = 0; i < hltConfig_.moduleLabels("HLT_L2DoubleMu23_NoVertex_v9").size(); i++){  // for simulation
//			std::cout<<hltConfig_.moduleLabels("HLT_DoublePhoton33_v2")[i]<<std::endl;
			
//			}
      // check if trigger name in (new) config
      if (triggerName_!="@") { // "@" means: analyze all triggers in config
	const unsigned int n(hltConfig_.size());
	const unsigned int triggerIndex(hltConfig_.triggerIndex(triggerName_));
	if (triggerIndex>=n) {
	  //cout << "HLTEventAnalyzerAOD::analyze:"
	   //    << " TriggerName " << triggerName_ 
	    //   << " not available in (new) config!" << endl;
	  //cout << "Available TriggerNames are: " << endl;
	  //hltConfig_.dump("Triggers");
	}
      }

      //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      //EXAMPLE: How to dump information from the Provenance
      // Uncomment the following lines if needed.
      //the hltConfig has many accessors
      //For details see the header of the class,HLTConfigProvider.h
      //To check the example, uncomment the lines below
      //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      //hltConfig_.dump("Streams");
      //hltConfig_.dump("Datasets"); 
      //hltConfig_.dump("PrescaleTable");
      //hltConfig_.dump("ProcessPSet");
      //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    }


  
  } else {
   // cout << "HLTEventAnalyzerAOD::analyze:"
	// << " config extraction failure with process name "
	 //<< processName_ << endl;
  }
  
}

// ------------ method called when ending the processing of a run  ------------
void 
ElectronAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
ElectronAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
ElectronAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ElectronAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

 //Specify that only 'tracks' is allowed
 //To use, remove the default given above and uncomment below
 //ParameterSetDescription desc;
 //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
 //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronAnalyzer);
