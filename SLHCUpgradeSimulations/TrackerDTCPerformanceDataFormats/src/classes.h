#ifndef SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H
#define SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H

#include "DataFormats/Common/interface/Wrapper.h"
#include "Rtypes.h"
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefHolder.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/OneToValue.h"
#include "DataFormats/Common/interface/OneToOne.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/OneToManyWithQuality.h"
#include "DataFormats/Common/interface/OneToManyWithQualityGeneric.h"
#include "DataFormats/Common/interface/View.h"

#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/DTCId.h"

#include <vector>

namespace SLHCUpgradeSimulations_TrackerDTCPerformanceDataFormats
{
  struct dictionary
  {
		
		
		
		
		
		
    std::bitset<reco::TrackBase::algoSize> ba;
    reco::TrackExtraCollection v3;
    edm::Wrapper<reco::TrackExtraCollection> c3;
    edm::Ref<reco::TrackExtraCollection> r3;
    edm::RefProd<reco::TrackExtraCollection> rp3;
    edm::RefVector<reco::TrackExtraCollection> rv3;

    std::vector<edm::RefVector<std::vector<reco::Track> > > vrv3;
    edm::Ptr<reco::Track> ptrt;
    std::vector<edm::Ptr<reco::Track> > vptrt;

    reco::TrackCollection v1;
    edm::Wrapper<reco::TrackCollection> c1;
    reco::TrackRef r1;
    reco::TrackRefProd rp1;
    reco::TrackRefVector rv1;
    edm::Wrapper<reco::TrackRefVector> wv1;
    std::vector<reco::TrackRef> vr1;

    edm::helpers::Key<edm::RefProd<std::vector<reco::Track> > > rpt1;
    edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, double, unsigned int> > am1;
    edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, float, unsigned int> > am2;
    edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, int, unsigned int> > am3;
    edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, bool, unsigned int> > am4;
    edm::Wrapper<edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, double, unsigned int> > > wam1;
    edm::Wrapper<edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, float, unsigned int> > > wam2;
    edm::Wrapper<edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, int, unsigned int> > >  wam3;
    edm::Wrapper<edm::AssociationMap<edm::OneToValue<std::vector<reco::Track>, bool, unsigned int> > > wam4;

    edm::Wrapper<edm::AssociationVector<reco::TrackRefProd,std::vector<double> > > wav1;
    edm::Wrapper<edm::AssociationVector<reco::TrackRefProd,std::vector<float> > > wav2;
    edm::Wrapper<edm::AssociationVector<reco::TrackRefProd,std::vector<int> > > wav3;
    edm::Wrapper<edm::AssociationVector<reco::TrackRefProd,std::vector<bool> > > wav4;

    edm::helpers::KeyVal<reco::TrackRef,reco::TrackRef> kvtttmap1;
    reco::TrackToTrackMap tttmap1;
    edm::Wrapper<reco::TrackToTrackMap> wtttmap1;

    // DEDX containers    
    reco::DeDxDataCollection dedxe1;
    reco::DeDxData dedxe2;
    reco::DeDxDataValueMap dedxe3;
 
    edm::Wrapper<reco::TrackDeDxHitsCollection> dedxw1; 
    edm::Wrapper<reco::DeDxDataCollection> dedxw2; 
    edm::Wrapper<reco::DeDxDataValueMap> dedxw3;

    // RefToBase Holders for Tracks
    edm::RefToBase<reco::Track>                         rtb_tk;
    edm::reftobase::IndirectHolder<reco::Track>         ih_tk;
    //edm::reftobase::BaseHolder<reco::Track>             bh_tk;
    edm::reftobase::RefHolder<reco::TrackRef>           rf_tkr;
    edm::reftobase::RefHolder<edm::Ptr<reco::Track> > rfh_ptr_tkr;
    edm::reftobase::Holder<reco::Track, reco::TrackRef> h_tk_tkr;
    std::vector< edm::RefToBase<reco::Track> >		rtb_tk_vect;

    reco::TrackBaseRefVector tbrv;
    edm::Wrapper<reco::TrackBaseRefVector> wtbrv;

    edm::RefToBaseProd<reco::Track> aaaaaa;
    std::vector<std::pair<edm::RefToBase<reco::Track>,double> > aaaaaaaaaa;
    std::pair<edm::RefToBase<reco::Track>,double> aaaaaaaaaaaa;

    edm::ValueMap<reco::TrackRefVector> vm_trv;
    edm::Wrapper<edm::ValueMap<reco::TrackRefVector> > w_vm_trv;

    edm::helpers::KeyVal<edm::RefProd<std::vector<reco::Track> >,edm::RefProd<std::vector<TrajectorySeed> > > x1;
    edm::AssociationMap<edm::OneToMany<std::vector<reco::Track>,std::vector<TrajectorySeed>,unsigned int> > x2;
    edm::Wrapper<edm::AssociationMap<edm::OneToMany<std::vector<reco::Track>,std::vector<TrajectorySeed>,unsigned int> > > x3;
    std::vector<std::pair<edm::Ref<std::vector<reco::Track>,reco::Track,edm::refhelper::FindUsingAdvance<std::vector<reco::Track>,reco::Track> >,float> > amf5;
    std::pair<edm::Ref<std::vector<reco::Track>,reco::Track,edm::refhelper::FindUsingAdvance<std::vector<reco::Track>,reco::Track> >,float> amf6;


    std::vector<std::pair<edm::Ref<std::vector<reco::Track>,reco::Track,edm::refhelper::FindUsingAdvance<std::vector<reco::Track>,reco::Track> >,int> > am5;
    std::pair<edm::Ref<std::vector<reco::Track>,reco::Track,edm::refhelper::FindUsingAdvance<std::vector<reco::Track>,reco::Track> >,int> am6;

    std::pair<reco::Track,reco::Track> trackPair;
    std::pair<TrackCandidate, std::pair<reco::Track,reco::Track> > ctpair;
    std::vector<std::pair<TrackCandidate, std::pair<reco::Track,reco::Track> > > candidateMap;
    edm::Wrapper<std::pair<reco::Track,reco::Track> > w1;
    edm::Wrapper<std::vector<std::pair<TrackCandidate, std::pair<reco::Track,reco::Track> > > > w2;
    edm::Wrapper<std::pair<TrackCandidate, std::pair<reco::Track,reco::Track> > > w3;

    std::pair<reco::TrackRef,reco::TrackRef> trackRefPair;
    std::pair<TrackCandidate, std::pair<reco::TrackRef,reco::TrackRef> > ctrpair;
    std::vector<std::pair<TrackCandidate, std::pair<reco::TrackRef,reco::TrackRef> > > candidateRefMap;
    edm::Wrapper<std::pair<reco::TrackRef,reco::TrackRef> > ww1;
    edm::Wrapper<std::vector<std::pair<TrackCandidate, std::pair<reco::TrackRef,reco::TrackRef> > > > ww2;
    edm::Wrapper<std::pair<TrackCandidate, std::pair<reco::TrackRef,reco::TrackRef> > > ww3;


    reco::DeDxHitInfo hitInfoDEDX;
    reco::DeDxHitInfoCollection hitInfoDEDXc;
    reco::DeDxHitInfoRef hitInfoDEDXr;
    reco::DeDxHitInfoRefProd hitInfoDEDXp;
    reco::DeDxHitInfoRefVector hitInfoDEDXv;
    reco::DeDxHitInfoAss hitInfoDEDXam;
    edm::Wrapper<reco::DeDxHitInfo> hitInfoDEDXW;
    edm::Wrapper<reco::DeDxHitInfoCollection> hitInfoDEDXcW;
    edm::Wrapper<reco::DeDxHitInfoAss> hitInfoDEDXamW;

    reco::DeDxHitInfo::DeDxHitInfoContainer hitInfoContainerDEDX;
    reco::DeDxHitInfo::DeDxHitInfoContainerCollection hitInfoContainerDEDXc;

  };
}

#endif // SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H
