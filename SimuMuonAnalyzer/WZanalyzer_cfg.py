import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )



process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA.db')
process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/START53_LV6A1.db')
#process.GlobalTag.globaltag = 'FT_53_LV5_AN1::All'
process.GlobalTag.globaltag = 'START53_LV6A1::All'


myfilelist = cms.untracked.vstring()
myfilelist.extend( ['root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/0013A453-7ABD-E311-AAC9-0025905A60F8.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/00846A75-09BC-E311-9D9F-002618FDA279.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/046B655D-F5BB-E311-B6A8-003048679214.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/0EEE04BF-FDBB-E311-9E20-0025905A60E4.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/144334CD-00BC-E311-8BF0-0025905A60D0.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/14837FAD-EABB-E311-A422-0025905A6064.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/168D3005-F9BB-E311-9551-002590596490.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/1A1CC59D-EDBB-E311-B9D5-003048678F84.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/1A455B55-F4BB-E311-B68E-002618943908.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/1CA3EAE7-D1BB-E311-8ED1-002618943913.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/1E050ACA-F3BB-E311-9BFA-0025905A60D6.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/2057C4C3-FFBB-E311-96D1-0025905A607E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/24E63A07-08BC-E311-87F0-0025905A497A.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/2E3AA6CD-FFBB-E311-BE4E-002590593878.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/3261A1C2-F8BB-E311-A562-0025905A6080.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/362F9A59-F1BB-E311-9D36-0025905A6090.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/3670113B-07BC-E311-BA70-0025905A60DE.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/3A5E614A-06BC-E311-8F63-0025905A48D6.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/4058789B-02BC-E311-AA5F-0025905A48BA.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/44754E49-08BC-E311-8BF3-0025905A60CE.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/481EE3E7-13BC-E311-8997-002618943950.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/48E9439C-F2BB-E311-B8BC-0025905A60AA.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/4C1EDC54-0EBC-E311-84C1-0026189438C0.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/4C6C6C5B-DDBC-E311-B85E-0025905A6104.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/4ECA0C26-F0BB-E311-8D23-0025905A607E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/505A16E8-F1BB-E311-99D8-0025905A6056.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/52392D38-04BC-E311-B671-003048FFD7C2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/5680B77C-E0BB-E311-A431-0025905A6118.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/62C8B826-09BC-E311-B468-003048FF86CA.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/64F76049-EFBB-E311-B1CC-002618943973.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/661F9F1F-06BC-E311-A3D2-0025905A6132.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/66EBD5C8-F5BB-E311-BA6F-003048FFCB9E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/6A890DCB-ECBB-E311-A9F0-00304867916E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/700A77FB-E9BB-E311-9DEB-003048FFD75C.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/702EC5A1-EFBB-E311-BBFE-002618FDA207.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/72C59106-F3BB-E311-9D63-002618943845.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/72EDBEEB-E5BB-E311-93DE-002618943967.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/7863BA70-07BC-E311-992F-0025905A605E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/7A4365B4-EBBB-E311-8F90-003048678EE2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/7AEE45E6-E7BB-E311-A97C-003048FFCB96.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/84D40AC6-EEBB-E311-99BA-002618943849.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/84EF21E8-F4BB-E311-AB56-002618943908.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/8A1A7738-FBBB-E311-8929-0025905A6092.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/9220B9B4-01BC-E311-BF1E-0025905A48EC.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/92EA23FA-E6BB-E311-A442-00304867D836.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/963A810A-F3BB-E311-8680-0025905A60D2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/96924765-0BBC-E311-8875-003048678EE2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/98D1C24B-04BC-E311-A8DF-0025905A609E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/9AF6B831-06BC-E311-B15B-0025905A6092.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/9CB13F07-E3BB-E311-86D3-0025905A60BE.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/9CD5D441-FEBB-E311-AE0D-0025905A6076.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/A6AB1CAE-0ABC-E311-9F03-0025905A48F2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/B65CA6BE-F0BB-E311-8703-0025905A608E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/B83C4D96-08BC-E311-BAFF-0025905A608E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/C08B105C-F6BB-E311-A81C-0025905A60E4.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/CAEA8A0C-03BC-E311-85E2-0025905A6060.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/D22303A3-08BC-E311-A5C6-0025905A60F8.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/D28F6EA0-FCBB-E311-8280-003048FFD71E.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/D29077A1-0ABC-E311-8664-003048678EE2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/D2914846-0CBC-E311-9794-003048678EE2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/E030CDDA-09BC-E311-980F-003048FFD7D4.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/E27FC8D2-10BC-E311-8AB4-0026189438D9.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/E4390CA8-0EBC-E311-B41D-0025905A48EC.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/E4A7E061-F9BB-E311-B628-0025905A613C.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/E87E13C1-F0BB-E311-9CDC-003048FFD730.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/EC399FA4-EFBB-E311-8EC0-002618943923.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/EECC6B70-E0BB-E311-9A3A-003048FFCB84.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/F4B67F29-0ABC-E311-9C5B-0025905A60F2.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/FA082E61-03BC-E311-A519-0025905A6094.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/FA658368-E0BB-E311-A654-002590596484.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/FA9EDC56-0ABC-E311-891A-0025905A6118.root',
'root://eospublic.cern.ch//eos/opendata/cms/MonteCarlo2011/Summer11LegDR/WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S13_START53_LV6-v1/00000/FC4BD7B5-0BBC-E311-AAF2-0025905A60DE.root'
] )


process.source = cms.Source("PoolSource",    
       fileNames = myfilelist
    
)

process.demo = cms.EDAnalyzer('SimuMuonAnalyzer'
    , tracks = cms.untracked.InputTag('generalTracks'),
      outFile = cms.string("file:WW_muon.root")
)


process.p = cms.Path(process.demo)
