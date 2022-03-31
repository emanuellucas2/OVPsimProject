#!/bin/bash

# File must be sourced from other RUN script 
if [ "$(basename -- $0 .sh)" == "selectOptions" ]; then
  echo "Error: Script ($0) should not be called directly"
else

    TRACEAFTER=${TRACEAFTER[0]}
    TRACECOUNT=${TRACECOUNT[0]}

    count=0
    while [ $count -lt 10 ]; do
      bme[$count]=""
      count=$((count + 1))
    done
    declare -i appRef=0
    bme[0]="selected ${APP}"
    bm[0]="Toggle Application Select "
    bm[1]="Include Custom Extension  "
    ba[1]="--extlib iss/cpu0/exInst=instructionExtensionLib"

    bm[2]="Instructions Executed     "
    ba[2]="--extlib iss/cpu0/exProf=imperas.com/intercept/instructionCoverage/1.0"

    bm[3]="Instruction Tracing       "
    # counts based upon application compilation to show custom instructions used in main()
    ba[3]="--trace --traceshowicount --tracechange --traceafter ${TRACEAFTER[0]} --tracecount ${TRACECOUNT[0]}"

    bm[4]="Timing Estimation         "
    ba[4]="--extlib iss/cpu0/exTT=timingToolLib \
           --callcommand 'iss/cpu0/exTT/cpucycles -on' \
           --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1' \
           --callcommand 'iss/cpu0/exTT/instructiondata -filename custom_instruction_timing.txt'"
    bm[5]="Timing Stretch            "
    ba[5]="--extlib iss/cpu0/exTT=timingToolLib \
           --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
           --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1' \
           --callcommand 'iss/cpu0/exTT/instructiondata -filename custom_instruction_timing.txt'"
    bm[6]="Application Code Coverage "
    ba[6]="--callcommand 'iss/cpu0/vapTools/linecoverage'"
    bm[7]="Application Profiling     "
    ba[7]="--callcommand 'iss/cpu0/vapTools/functionprofile'"

    bm[8]="Instruction Implementation Profile "
    ba[8]="--profile 40"
    bm[9]="Model Code Coverage       "
    ba[9]="--vlnvroot $(pwd)/vlnvroot --vlnvmap riscv.ovpworld.org/processor/riscv/1.0=riscv.ovpworld.org/processor/riscv-gcov/1.0"

    bm[10]="Debug Session             "
    ba[10]="--mpdegui"

    bm[11]="Instruction Profile       "
    ba[11]="--extlib iss/cpu0/exInstProf=imperas.com/intercept/instructionProfile/1.0"

    maxitem=12

    bm[20]="Run Simulation            "
    bm[40]="Generate PDF Document     "
    bm[41]="Generate LaTex Document   "
    bm[42]="View Model Code Coverage  "

    declare -i run=0
    declare -i maxselections=15
    while [ $run = 0 ]; do
      index=0
      while [ $index -lt $maxitem ]; do
        echo " $index: ${bm[${index}]} ${bme[${index}]}"
        index=$((index + 1))
      done
      echo "20: ${bm[20]} ${COMMANDLINE} --program application/${APP}"
      echo "----"
      echo "40: ${bm[40]}"
      echo "41: ${bm[41]}"
      echo "42: ${bm[42]}"
      echo "99: exit (without running)"
    
      bmn=0
      echo ""
      echo -n 'Please Select an Option: '
      read bmn

      if [ "$bmn" = "" ]; then
        echo "Invalid entry, a number is required"
    
      else
        case $bmn in
          0)
            if [ $appRef -eq 0 ]; then appRef=1; else appRef=0; fi
            APP=${applications[$appRef]}
            bme[0]="selected ${APP}"
            if [ "${bme[3]}" != "" ]; then
              # Update trace
              ba[3]="--trace --traceshowicount --tracechange --traceafter ${TRACEAFTER[$appRef]} --tracecount ${TRACECOUNT[$appRef]}"
              TRACEARGS=${ba[3]}
              bme[3]="enabled: ${TRACEARGS}"
            fi
            ;;
          1)
            CUSTOMARGS=${ba[1]}
            bme[1]="enabled: ${CUSTOMARGS}"
            ;;
          2)
            INSTCOVARGS=${ba[2]}
            bme[2]="enabled: ${INSTCOVARGS}"
            ;;
          3)
            ba[3]="--trace --traceshowicount --tracechange --traceafter ${TRACEAFTER[$appRef]} --tracecount ${TRACECOUNT[$appRef]}"
            TRACEARGS=${ba[3]}
            bme[3]="enabled: ${TRACEARGS}"
            ;;
          4)
            if [ "${bme[5]}" != "" ]; then
              echo "Warning: Timing Tool Library option already selected"
            else
              TIMINGARGS=${ba[4]}
              bme[4]="enabled: ${TIMINGARGS}"
            fi
            ;;
          5)
            if [ "${bme[4]}" != "" ]; then
              echo "Warning: Timing Tool Library option already selected"
            else
              STRETCHARGS=${ba[5]}
              bme[5]="enabled: ${STRETCHARGS}"
            fi
            ;;
          6)
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              bme[6]=" Not Available: VAP Tool install is required"
            else
              APPCOVARGS=${ba[6]}
              bme[6]="enabled: ${APPCOVARGS}"
              export POSTRUN="egui.exe -open iss_cpu0.icov"
            fi
            ;;
          7)
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              bme[7]=" Not Available: VAP Tool install is required"
            else
              APPPROFARGS=${ba[7]}
              bme[7]="enabled: ${APPPROFARGS}"
              export POSTRUN="egui.exe -open iss_cpu0.iprof"
            fi
            ;;
          8)
            INSTIMPLPROFARGS=${ba[8]}
            bme[8]="enabled: ${INSTIMPLPROFARGS}"
            ;;
          9)
            VLNVARGS=${ba[9]}
            bme[9]="enabled: ${VLNVARGS}"
            # build libraries for GCOV run
            echo "Building Models for Code Coverage"
            make build-gcov
            ;;
          10)
            DEBUGARGS=${ba[10]}
            bme[10]="enabled: ${DEBUGARGS}"
            ;;
          11)
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              bme[11]=" Not Available: VAP Tool install is required"
            else
              INSTPROFARGS=${ba[11]}
              bme[11]="enabled: ${INSTPROFARGS}"
            fi
            ;;
          20)
            # Options 6, 7 and 11 if set require standard tools to be loaded
            if [ "${APPCOVARGS}" != "" ] || [ "${APPPROFARGS}" != "" ] || [ "${INSTPROFARGS}" != "" ]; then
                ADDSTDTOOLS="--enabletools"
            fi
            # break out of loop to run
            run=1
            ;;
          40)
             if [ "${IMPERAS_UNAME}" = "Linux" ]; then
               echo "Generating PDF Document"
               make pdf
             else
               echo "PDF Document Generation not available on Windows"
             fi
             return 1
            ;;
          41)
             echo "Generating LaTex Document"
             make tex
             return 1
            ;;
          42)
             echo "Starting Coverage Output viewer"
             make view
             return 1
            ;;
          99)
            return 1
            ;;
          *)
            echo "Invalid entry"
            ;;
          esac
      fi
      if [ $maxselections -le 0 ]; then
          echo "Too many selections ... stopping"
          return 1
      fi
      maxselections=$(($maxselections - 1))
    done
    return 0

fi # end of check this script was sourced
return 1
