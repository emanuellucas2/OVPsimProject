#!/bin/bash

# File must be sourced from other RUN script 
if [ "$(basename -- $0 .sh)" == "selectStage" ]; then
  echo "Error: Script ($0) should not be called directly"
else

    TRACEAFTER=${TRACEAFTER[0]}
    TRACECOUNT=${TRACECOUNT[0]}

    count=0
    maxitem=40
    while [ $count -lt $maxitem ]; do
      bm[$count]=""
      count=$((count + 1))
    done
    bm[1]="Instruction Accurate simulation"
    bm[2]="Cycle Approximate simulation"
    bm[3]="Basic Block Profile"
    bm[4]="Function Profile"

    bm[5]="Add custom instructions to application"
    bm[6]="Add custom instructions to model"
    bm[7]="Cycle Approximate simulation"
    bm[8]="Function Profile"

    bm[9]="Trace custom instructions"
    bm[10]="Debug custom instructions"

#    bm[11]="Instruction Profile"

    bm[15]="Documenting custom instructions (PDF)"
    bm[16]="Documenting custom instructions (TEX)"

    bm[20]="Custom Instruction Coverage"
    bm[21]="Custom Instruction Called C Function Profile"
    bm[22]="Custom Instruction Implementation Profile"

    bm[25]="Model Source Line Coverage"

    declare -i finished=99
    declare -i maxselections=4
    while [ $finished -eq 99 ]; do
      index=0
      while [ $index -lt $maxitem ]; do
        if [ $index -eq 0 ]; then
          echo "--- C Application ---"
        fi
        if [ $index -eq 5 ]; then
          echo "--- Custom Instruction Application ---"
        fi
        if [ $index -eq 9 ]; then
          echo "--- Debugging Operations ---"
        fi
        if [ $index -eq 15 ]; then
          echo "--- Documentation Generation ---"
        fi
        if [ $index -eq 20 ]; then
          echo "--- Custom Instruction Implementation Analysis ---"
        fi
        if [ $index -eq 99 ]; then
          echo "---  ---"
        fi
        if [ "${bm[$index]}" != "" ]; then
          echo " $index: ${bm[${index}]}"
        fi
        index=$((index + 1))
      done
      echo " 99: exit (without running)"
    
      bmn=0
      echo ""
      echo -n 'Please Select an Option: '
      read bmn

      if [ "$bmn" = "" ]; then
        echo "Invalid entry, a number is required"
    
      else
        case $bmn in
          1)
            # Instruction Accurate simulation
            egui.exe -open application/test_lib_c.c;echo "Paused .. press key start simulation";read
            APP=${applications[1]}
            finished=0
            ;;
          2)
            # Cycle Approximate simulation
            egui.exe -open timingToolLib/timingTool.c;echo "Paused .. press key start simulation";read
            APP=${applications[1]}
            STRETCHARGS="--extlib iss/cpu0/exTT=timingToolLib \
             --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
             --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1'"
            finished=0
            ;;
          3)
            # Basic Block Profile
            APP=${applications[1]}
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              echo "** VAP Tool install is required"
              finished=4
            else
              STRETCHARGS="--extlib iss/cpu0/exTT=timingToolLib \
               --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
               --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1'"
              APPPROFARGS="--extlib iss/cpu0/exInstProf=imperas.com/intercept/bbProfile/1.0 --override iss/cpu0/exInstProf/filename=bbProfile_c.txt --enabletools"
              export POSTRUN="egui.exe -open bbProfile_c.txt"
              finished=0
            fi
            ;;
          4)
            # Function Profile
            APP=${applications[1]}
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              echo "** VAP Tool install is required"
              finished=4
            else
              STRETCHARGS="--extlib iss/cpu0/exTT=timingToolLib \
               --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
               --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1'"
              APPPROFARGS="--enabletools --callcommand 'iss/cpu0/vapTools/functionprofile -sampleinterval 10' --quantum 0.00001"
              export POSTRUN="egui.exe -open iss_cpu0.iprof"
              finished=0
            fi
            ;;
          5)
            # Add custom instructions to application
            egui.exe -open application/test_lib_asm.c;echo "Paused .. press key start simulation";read
            APP=${applications[0]}
            finished=0
            ;;
          6)
            # Add custom instructions to model
            egui.exe -open instructionExtensionLib/customChaCha20.c;egui.exe -open instructionExtensionCFunctionCallLib/customChaCha20_CallC.c;echo "Paused .. press key start simulation";read
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib --showload"
            finished=0
            ;;
          7)
            # Cycle Approximate simulation
            egui.exe -open custom_instruction_timing.txt;echo "Paused .. press key start simulation";read
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
            STRETCHARGS="--extlib iss/cpu0/exTT=timingToolLib \
               --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
               --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1' \
               --callcommand 'iss/cpu0/exTT/instructiondata -filename custom_instruction_timing.txt'"
            finished=0
            ;;
          8)
            # Function Profile
            APP=${applications[0]}
            checkinstall.exe -group vap -p install.pkg --nobanner
            if [ $? -ne 0 ]; then
              echo "** VAP Tool install is required"
              finished=4
            else
              CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
              STRETCHARGS="--extlib iss/cpu0/exTT=timingToolLib \
                 --callcommand 'iss/cpu0/exTT/cpucycles -on -stretch' \
                 --callcommand 'iss/cpu0/exTT/memorycycles -low 0x28000 -high 0x28fff -feCycles 0 -ldCycles 2 -stCycles 1' \
                 --callcommand 'iss/cpu0/exTT/instructiondata -filename custom_instruction_timing.txt'"
              APPPROFARGS="--enabletools --callcommand 'iss/cpu0/vapTools/functionprofile -sampleinterval 1' --quantum 0.00001"
              export POSTRUN="egui.exe -open iss_cpu0.iprof"
              finished=0
            fi
            ;;
          9)
            # Trace custom instructions
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
            TRACEARGS="--trace --traceshowicount --tracechange --traceafter ${TRACEAFTER[0]} --tracecount ${TRACECOUNT[0]}"
            finished=0
            ;;
          10)
            # Debug custom instructions
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
            DEBUGARGS="--mpdegui"
            finished=0
            ;;
#          11)
#            APP=${applications[0]}
#            checkinstall.exe -group vap -p install.pkg --nobanner
#            if [ $? -ne 0 ]; then
#              echo "** VAP Tool install is required"
#              finished=4
#            else
#              CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib --extlib iss/cpu0/exInstProf=imperas.com/intercept/instructionProfile/1.0 --enabletools"
#              export POSTRUN="ls -al ipr.cpu0; cat ipr.cpu0/processLine.ipr.txt"
#              finished=0
#            fi
#            ;;
          15)
            # Documenting custom instructions
            # PDF generation only on Linux
            if [ "${IMPERAS_UNAME}" = "Linux" ]; then
              echo "Generating PDF Document"
              make pdf
              evince pdf/*.pdf
            else
              echo "** PDF generation not available on Windows"
              echo "**   Please view pre-generated file pdf/OVP_Model_Specific_Information_riscv_RV32IM.pdf"
              
            fi
            finished=4
            ;;
          16)
            # Documenting custom instructions
            # TEX generation only on Linux
            echo "Generating TEX Document"
            make tex
            echo "** LaTex file available tex/OVP_Model_Specific_Information_riscv_RV32IM.tex"
            finished=4
            ;;
          20)
            # Custom Instruction Coverage
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
            INSTCOVARGS="--extlib iss/cpu0/exProf=imperas.com/intercept/instructionCoverage/1.0"
            export POSTRUN="cat coverageReports/cpu0.icr.txt"
            finished=0
            ;;
          21)
            # Custom Instruction Called C Function Profile
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionCFunctionCallLib"
            INSTIMPLPROFARGS="--profile -40"
            finished=0
            ;;
          22)
            # Custom Instruction Implementation Profile
            APP=${applications[0]}
            CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
            INSTIMPLPROFARGS="--profile -40"
            finished=0
            ;;
          25)
            # Model Source Line Coverage
            if [ "${IMPERAS_UNAME}" = "Linux" ]; then
              APP=${applications[0]}
              CUSTOMARGS="--extlib iss/cpu0/exInst=instructionExtensionLib"
              VLNVARGS="--vlnvroot $(pwd)/vlnvroot --vlnvmap riscv.ovpworld.org/processor/riscv/1.0=riscv.ovpworld.org/processor/riscv-gcov/1.0"
              # build libraries for GCOV run
              echo "Building Models for Code Coverage"
              make build-gcov
              export POSTRUN="make view"
              finished=0
            else
              echo "** Model Source Line Coverage not available on Windows. Opening pre-generated file"
              egui.exe -open pre/coverage.lcov
              finished=4
            fi
            ;;
          99)
            finished=4
            ;;
          *)
            echo "Invalid entry"
            ;;
          esac
      fi
      if [ $maxselections -le 0 ]; then
          echo "Too many attempts ... stopping"
          finished=4
      fi
      maxselections=$(($maxselections - 1))
    done
    return $finished

fi # end of check this script was sourced
return 1
