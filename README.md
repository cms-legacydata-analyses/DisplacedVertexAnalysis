# DisplacedVertexAnalysis
## Description
## Requirements
This analysis example is met to be run within  [CMS VM 2011](http://opendata.cern.ch/record/252 "CMS VM Image") and utilizes CMSSW_5_3_32.

## How to run
### Setup
Within a terminal:
1. Create a CMSSW_5_3_32 environment, change directory into `CMSSW_5_3_32/src/` and clone this repository
```
cmsrel CMSSW_5_3_32
cd CMSSW_5_3_32/src
git clone git@github.com:cms-legacydata-analyses/DisplacedVertexAnalysis.git
```
Next set up CMS environment and compile the code

```
cmsenv
scram b
```
The analysis code is now ready to be run
### Running analysis
The analysis code is divided into four modules, corresponding to the diferent options: Data, Mc, electron channel and muon channel. To run one of them, change into the corresponding directory and run the configuration file with `cmsRun` executable. For example if you whant to run Electron MC:

```
cd SimuElectronAnalyzer
cmsRun simuelectronanalyzer_cfg.py
```
The output file will be named `simu_electron.root` (For the other cases: `muon.root`, `electron.root` and `simu_muon.root`).
## Creating Plots
The ploting scripts are located under `CMSSW_5_3_32/src/()/Plots`
