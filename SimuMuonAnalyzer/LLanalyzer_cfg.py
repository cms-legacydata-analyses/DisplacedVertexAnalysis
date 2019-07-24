import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )



process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA.db')
process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/START53_LV6A1.db')
#process.GlobalTag.globaltag = 'FT_53_LV5_AN1::All'
process.GlobalTag.globaltag = 'START53_LV6A1::All'

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
'file:simu/LLmuon10.root',
'file:simu/LLmuon11.root',
'file:simu/LLmuon12.root',
'file:simu/LLmuon13.root',
'file:simu/LLmuon14.root',
'file:simu/LLmuon15.root',
'file:simu/LLmuon16.root',
'file:simu/LLmuon1.root',
'file:simu/LLmuon2.root',
'file:simu/LLmuon3.root',
'file:simu/LLmuon4.root',
'file:simu/LLmuon5.root',
'file:simu/LLmuon6.root',
'file:simu/LLmuon7.root',
'file:simu/LLmuon8.root',
'file:simu/LLmuon9.root'
   )
)

process.demo = cms.EDAnalyzer('SimuMuonAnalyzer'
    , tracks = cms.untracked.InputTag('generalTracks'),
      outFile = cms.string("file:LL_muon.root")
)


process.p = cms.Path(process.demo)
