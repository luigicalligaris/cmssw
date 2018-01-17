#ifndef SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H
#define SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H

#include "Rtypes.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/PtrVector.h"
#include "DataFormats/Common/interface/RefHolder.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/OneToValue.h"
#include "DataFormats/Common/interface/OneToOne.h"
#include "DataFormats/Common/interface/OneToManyWithQuality.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/Phase2TrackerCluster/interface/Phase2TrackerCluster1D.h"

#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/DTCId.h"
#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/Hash.h"

#include <vector>


// Note: see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideEDMRef for a description of the different EDM helper templates
namespace SLHCUpgradeSimulations_TrackerDTCPerformanceDataFormats
{
	struct dictionary
	{
		TrackerDTCPerformance::DTCId                                                                                                                                   dummy_dtcid;
		std::vector<TrackerDTCPerformance::DTCId>                                                                                                                      dummy_stdvec_dtcid;
		edm::Ref<std::vector<TrackerDTCPerformance::DTCId>>                                                                                                            dummy_edmref_dtcid;
		edm::RefVector<std::vector<TrackerDTCPerformance::DTCId>>                                                                                                      dummy_edmrefvec_dtcid;
		edm::Ptr<TrackerDTCPerformance::DTCId>                                                                                                                         dummy_edmptr_dtcid;
		edm::PtrVector<std::vector<TrackerDTCPerformance::DTCId>>                                                                                                      dummy_edmptrvec_dtcid;
		edm::RefProd<TrackerDTCPerformance::DTCId>                                                                                                                     dummy_edmrefprod_dtcid;
		edm::RefProd<std::vector<TrackerDTCPerformance::DTCId>>                                                                                                        dummy_edmrefprod_dtcidvec;
		edm::AssociationMap<edm::OneToValue           <std::vector<DetId>                       , TrackerDTCPerformance::DTCId                     > >                 dummy_onetoval_detid_dtcid;
		edm::AssociationMap<edm::OneToOne             <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>        > >                 dummy_onetoone_detid_dtcid;
		edm::AssociationMap<edm::OneToMany            <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>        > >                 dummy_onetomany_detid_dtcid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, bool  > >                 dummy_onetomanywithqualo_detid_dtcid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, int   > >                 dummy_onetomanywithquali_detid_dtcid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, float > >                 dummy_onetomanywithqualf_detid_dtcid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, double> >                 dummy_onetomanywithquald_detid_dtcid;
		edm::AssociationMap<edm::OneToValue           <std::vector<TrackerDTCPerformance::DTCId>, DetId                                            > >                 dummy_onetoval_dtcid_detid;
		edm::AssociationMap<edm::OneToOne             <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                               > >                 dummy_onetoone_dtcid_detid;
		edm::AssociationMap<edm::OneToMany            <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                               > >                 dummy_onetomany_dtcid_detid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , bool  > >                 dummy_onetomanywithqualo_dtcid_detid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , int   > >                 dummy_onetomanywithquali_dtcid_detid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , float > >                 dummy_onetomanywithqualf_dtcid_detid;
		edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , double> >                 dummy_onetomanywithquald_dtcid_detid;
		edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<bool  > >                                                         dummy_assveco_dtcid_detid;
		edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<int   > >                                                         dummy_assveci_dtcid_detid;
		edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<float > >                                                         dummy_assvecf_dtcid_detid;
		edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<double> >                                                         dummy_assvecd_dtcid_detid;
		edm::Wrapper< TrackerDTCPerformance::DTCId                                                                                                                   > dummy_wrapper_dtcid;
		edm::Wrapper< std::vector<TrackerDTCPerformance::DTCId>                                                                                                      > dummy_wrapper_stdvec_dtcid;
		edm::Wrapper< edm::Ref<std::vector<TrackerDTCPerformance::DTCId>>                                                                                            > dummy_wrapper_edmref_dtcid;
		edm::Wrapper< edm::RefVector<std::vector<TrackerDTCPerformance::DTCId>>                                                                                      > dummy_wrapper_edmrefvec_dtcid;
		edm::Wrapper< edm::Ptr<TrackerDTCPerformance::DTCId>                                                                                                         > dummy_wrapper_edmptr_dtcid;
		edm::Wrapper< edm::PtrVector<std::vector<TrackerDTCPerformance::DTCId>>                                                                                      > dummy_wrapper_edmptrvec_dtcid;
		edm::Wrapper< edm::RefProd<TrackerDTCPerformance::DTCId>                                                                                                     > dummy_wrapper_edmrefprod_dtcid;
		edm::Wrapper< edm::RefProd<std::vector<TrackerDTCPerformance::DTCId>>                                                                                        > dummy_wrapper_edmrefprod_dtcidvec;
		edm::Wrapper< edm::AssociationMap<edm::OneToValue           <std::vector<DetId>                       , TrackerDTCPerformance::DTCId                     > > > dummy_wrapper_onetoval_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToOne             <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>        > > > dummy_wrapper_onetoone_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToMany            <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>        > > > dummy_wrapper_onetomany_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, bool  > > > dummy_wrapper_onetomanywithqualo_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, int   > > > dummy_wrapper_onetomanywithquali_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, float > > > dummy_wrapper_onetomanywithqualf_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<DetId>                       , std::vector<TrackerDTCPerformance::DTCId>, double> > > dummy_wrapper_onetomanywithquald_detid_dtcid;
		edm::Wrapper< edm::AssociationMap<edm::OneToValue           <std::vector<TrackerDTCPerformance::DTCId>, DetId                                            > > > dummy_wrapper_onetoval_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToOne             <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                               > > > dummy_wrapper_onetoone_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToMany            <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                               > > > dummy_wrapper_onetomany_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , bool  > > > dummy_wrapper_onetomanywithqualo_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , int   > > > dummy_wrapper_onetomanywithquali_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , float > > > dummy_wrapper_onetomanywithqualf_dtcid_detid;
		edm::Wrapper< edm::AssociationMap<edm::OneToManyWithQuality <std::vector<TrackerDTCPerformance::DTCId>, std::vector<DetId>                       , double> > > dummy_wrapper_onetomanywithquald_dtcid_detid;
		edm::Wrapper< edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<bool  > >                                         > dummy_wrapper_assveco_dtcid_detid;
		edm::Wrapper< edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<int   > >                                         > dummy_wrapper_assveci_dtcid_detid;
		edm::Wrapper< edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<float > >                                         > dummy_wrapper_assvecf_dtcid_detid;
		edm::Wrapper< edm::AssociationVector<edm::RefProd<std::vector<TrackerDTCPerformance::DTCId> >, std::vector<double> >                                         > dummy_wrapper_assvecd_dtcid_detid;
		
	};
}

#endif // SLHCUPGRADESIMULATIONS_TRACKERDTCPERFORMANCEDATAFORMATS_CLASSES_H
