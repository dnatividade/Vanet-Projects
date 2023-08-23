#
# OMNeT++/OMNEST Makefile for $(LIB_PREFIX)veins
#
# This file was generated with the command:
#  opp_makemake --make-so -f --deep -o veins -O out -pVEINS -I. -I.
#

# Name of target to be created (-o option)
TARGET_DIR = .
TARGET_NAME = $(LIB_PREFIX)veins$(D)
TARGET = $(TARGET_NAME)$(SHARED_LIB_SUFFIX)
TARGET_IMPLIB = $(TARGET_NAME)$(IMPLIB_SUFFIX)
TARGET_IMPDEF = $(TARGET_NAME)$(IMPDEF_SUFFIX)
TARGET_FILES = $(TARGET_DIR)/$(TARGET)

# C++ include paths (with -I)
INCLUDE_PATH = -I. -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/veins/base/connectionManager/BaseConnectionManager.o \
    $O/veins/base/connectionManager/ChannelAccess.o \
    $O/veins/base/connectionManager/ConnectionManager.o \
    $O/veins/base/connectionManager/NicEntryDebug.o \
    $O/veins/base/connectionManager/NicEntryDirect.o \
    $O/veins/base/modules/BaseApplLayer.o \
    $O/veins/base/modules/BaseBattery.o \
    $O/veins/base/modules/BaseLayer.o \
    $O/veins/base/modules/BaseMacLayer.o \
    $O/veins/base/modules/BaseMobility.o \
    $O/veins/base/modules/BaseModule.o \
    $O/veins/base/modules/BaseWorldUtility.o \
    $O/veins/base/modules/BatteryAccess.o \
    $O/veins/base/phyLayer/Antenna.o \
    $O/veins/base/phyLayer/BaseDecider.o \
    $O/veins/base/phyLayer/BasePhyLayer.o \
    $O/veins/base/phyLayer/ChannelInfo.o \
    $O/veins/base/phyLayer/Decider.o \
    $O/veins/base/phyLayer/PhyUtils.o \
    $O/veins/base/toolbox/Signal.o \
    $O/veins/base/toolbox/SignalUtils.o \
    $O/veins/base/toolbox/Spectrum.o \
    $O/veins/base/utils/Coord.o \
    $O/veins/base/utils/Heading.o \
    $O/veins/base/utils/NedFunctions.o \
    $O/veins/base/utils/NetwToMacControlInfo.o \
    $O/veins/base/utils/SimpleAddress.o \
    $O/veins/base/utils/winsupport.o \
    $O/veins/modules/analogueModel/BreakpointPathlossModel.o \
    $O/veins/modules/analogueModel/NakagamiFading.o \
    $O/veins/modules/analogueModel/PERModel.o \
    $O/veins/modules/analogueModel/SimpleObstacleShadowing.o \
    $O/veins/modules/analogueModel/SimplePathlossModel.o \
    $O/veins/modules/analogueModel/TwoRayInterferenceModel.o \
    $O/veins/modules/analogueModel/VehicleObstacleShadowing.o \
    $O/veins/modules/application/ieee80211p/DemoBaseApplLayer.o \
    $O/veins/modules/application/traci/MyVeinsApp.o \
    $O/veins/modules/application/traci/TraCIDemo11p.o \
    $O/veins/modules/application/traci/TraCIDemoRSU11p.o \
    $O/veins/modules/mac/ieee80211p/Mac1609_4.o \
    $O/veins/modules/mobility/LinearMobility.o \
    $O/veins/modules/mobility/traci/TraCIBuffer.o \
    $O/veins/modules/mobility/traci/TraCIColor.o \
    $O/veins/modules/mobility/traci/TraCICommandInterface.o \
    $O/veins/modules/mobility/traci/TraCIConnection.o \
    $O/veins/modules/mobility/traci/TraCICoordinateTransformation.o \
    $O/veins/modules/mobility/traci/TraCILauncher.o \
    $O/veins/modules/mobility/traci/TraCIMobility.o \
    $O/veins/modules/mobility/traci/TraCIRegionOfInterest.o \
    $O/veins/modules/mobility/traci/TraCIScenarioManager.o \
    $O/veins/modules/mobility/traci/TraCIScenarioManagerForker.o \
    $O/veins/modules/mobility/traci/TraCIScenarioManagerLaunchd.o \
    $O/veins/modules/mobility/traci/TraCIScreenRecorder.o \
    $O/veins/modules/mobility/traci/TraCIVehicleInserter.o \
    $O/veins/modules/obstacle/MobileHostObstacle.o \
    $O/veins/modules/obstacle/Obstacle.o \
    $O/veins/modules/obstacle/ObstacleControl.o \
    $O/veins/modules/obstacle/VehicleObstacleControl.o \
    $O/veins/modules/phy/Decider80211p.o \
    $O/veins/modules/phy/NistErrorRate.o \
    $O/veins/modules/phy/PhyLayer80211p.o \
    $O/veins/modules/phy/SampledAntenna1D.o \
    $O/veins/modules/utility/BBoxLookup.o \
    $O/veins/modules/utility/HasLogProxy.o \
    $O/veins/modules/utility/TimerManager.o \
    $O/veins/modules/world/annotations/AnnotationDummy.o \
    $O/veins/modules/world/annotations/AnnotationManager.o \
    $O/veins/modules/world/traci/trafficLight/TraCITrafficLightInterface.o \
    $O/veins/modules/world/traci/trafficLight/TraCITrafficLightProgram.o \
    $O/veins/modules/world/traci/trafficLight/logics/TraCITrafficLightAbstractLogic.o \
    $O/veins/modules/world/traci/trafficLight/logics/TraCITrafficLightSimpleLogic.o \
    $O/veins/visualizer/roads/RoadsCanvasVisualizer.o \
    $O/veins/visualizer/roads/RoadsOsgVisualizer.o \
    $O/veins/common_m.o \
    $O/veins/base/messages/AirFrame_m.o \
    $O/veins/base/messages/BorderMsg_m.o \
    $O/veins/base/messages/MacPkt_m.o \
    $O/veins/base/toolbox/Signal_m.o \
    $O/veins/base/utils/Coord_m.o \
    $O/veins/base/utils/POA_m.o \
    $O/veins/base/utils/SimpleAddress_m.o \
    $O/veins/modules/application/traci/TraCIDemo11pMessage_m.o \
    $O/veins/modules/messages/AckTimeOutMessage_m.o \
    $O/veins/modules/messages/AirFrame11p_m.o \
    $O/veins/modules/messages/BaseFrame1609_4_m.o \
    $O/veins/modules/messages/DemoSafetyMessage_m.o \
    $O/veins/modules/messages/DemoServiceAdvertisement_m.o \
    $O/veins/modules/messages/Mac80211Ack_m.o \
    $O/veins/modules/messages/Mac80211Pkt_m.o \
    $O/veins/modules/messages/PhyControlMessage_m.o \
    $O/veins/modules/messages/TraCITrafficLightMessage_m.o

# Message files
MSGFILES = \
    veins/common.msg \
    veins/base/messages/AirFrame.msg \
    veins/base/messages/BorderMsg.msg \
    veins/base/messages/MacPkt.msg \
    veins/base/toolbox/Signal.msg \
    veins/base/utils/Coord.msg \
    veins/base/utils/POA.msg \
    veins/base/utils/SimpleAddress.msg \
    veins/modules/application/traci/TraCIDemo11pMessage.msg \
    veins/modules/messages/AckTimeOutMessage.msg \
    veins/modules/messages/AirFrame11p.msg \
    veins/modules/messages/BaseFrame1609_4.msg \
    veins/modules/messages/DemoSafetyMessage.msg \
    veins/modules/messages/DemoServiceAdvertisement.msg \
    veins/modules/messages/Mac80211Ack.msg \
    veins/modules/messages/Mac80211Pkt.msg \
    veins/modules/messages/PhyControlMessage.msg \
    veins/modules/messages/TraCITrafficLightMessage.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
CONFIGFILE = $(shell opp_configfilepath)
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) $(IMPORT_DEFINES) -DVEINS_EXPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH) -PVEINS_API
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE (if COPTS has changed since last build)
# and make the object files depend on it
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
  $(shell $(MKPATH) "$O")
  $(file >$(COPTS_FILE),$(COPTS))
endif

# On Windows, the target has additional file(s). An import lib and an optional debug symbol file is created too.
ifeq ($(PLATFORM),win32.x86_64)
  TARGET_FILES+= $(TARGET_DIR)/$(TARGET_IMPDEF) $(TARGET_DIR)/$(TARGET_IMPLIB)
  LDFLAGS+=$(LDFLAG_IMPDEF)$O/$(TARGET_IMPDEF) $(LDFLAG_IMPLIB)$O/$(TARGET_IMPLIB)
  ifeq ($(TOOLCHAIN_NAME),clang-msabi)
    ifeq ($(MODE),debug)
      TARGET_FILES+=$(TARGET_DIR)/$(TARGET_NAME).pdb
    endif
  endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
-include makefrag

#------------------------------------------------------------------------------

# Main target
all: $(TARGET_FILES)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clang-msabi)
	-$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib) 2>/dev/null
endif

$O/$(TARGET) $O/$(TARGET_IMPDEF) $O/$(TARGET_IMPLIB) &: $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)
ifeq ($(PLATFORM),win32.x86_64)
	$(Q)llvm-ar d $O/$(TARGET_IMPLIB) $(TARGET) # WORKAROUND: throw away the first file from the archive to make the LLD generated import lib valid
endif

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_FILES)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(CLEANALL_COMMAND)
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

help:
	@echo "$$HELP_SYNOPSYS"
	@echo "$$HELP_TARGETS"
	@echo "$$HELP_VARIABLES"
	@echo "$$HELP_EXAMPLES"

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
