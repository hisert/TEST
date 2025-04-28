#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c task.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/task.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o
POSSIBLE_DEPFILES=${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/ssd1306_oled.o.d ${OBJECTDIR}/input_debounce.o.d ${OBJECTDIR}/buton_debounce.o.d ${OBJECTDIR}/thread.o.d ${OBJECTDIR}/soft_i2c.o.d ${OBJECTDIR}/PIC_18F87K22.o.d ${OBJECTDIR}/task.o.d ${OBJECTDIR}/MENU.o.d ${OBJECTDIR}/ATMEGA_64.o.d ${OBJECTDIR}/ssh1106_oled.o.d ${OBJECTDIR}/ATMEGA_328.o.d ${OBJECTDIR}/AS5600_MAS.o.d ${OBJECTDIR}/ws2812b.o.d ${OBJECTDIR}/eeprom.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/task.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o

# Source Files
SOURCEFILES=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c task.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega64
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/782aabf7074ab42229af28c6d03a4ff5fb28a418 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/bd80295eb5c4b2441768be73b1d0c11997bd0936 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/6a90f559383edffb672096328fa317610f980aa .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/d254eccd808b0cad064e87dacb6791b08273d32d .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/4bced34ed7d819e5cc5712031c5627cfeaec373e .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/ca992901bcf33bf484e96ad44bcc44e5baf76d14 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/efe0cebf87f6cfc4da1f74a488eb6a6f836827f6 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/task.o: task.c  .generated_files/flags/default/b0220a1f7998e9305a3cb7ef6d38afb6b9f6c7ae .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/task.o.d 
	@${RM} ${OBJECTDIR}/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/task.o.d" -MT "${OBJECTDIR}/task.o.d" -MT ${OBJECTDIR}/task.o -o ${OBJECTDIR}/task.o task.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/290f255dfb71b40d50ad5bd9592c192b553b5e6d .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/b05ee09dae7acbf733131d85a6e60c38777a6f34 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/107ae07946827174c40eaa23a7c9deec1d6cdaee .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/2fe2303dd3901b389de7ef64a3c4a0fb09f89959 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/53ab8495a23beb298fc673a39591e86ca94f5675 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/21c1007e38e97279b0b60f1b1e619ca0f4659dec .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/852cb9ff463ed270448c429ae829b1e6269963cd .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
else
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/69786bb4b8ae310b1975675df3d16017f29e7f43 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/489eca7d4639f5f23e2da23255ae3d2965827b42 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/648a934ffa804f30a7dad52c10a6c5602c3ed990 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/563206bc1562f9db8c048c9cfeb603a4618d45a6 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/cb56220d7fbd13ad548f759f7360b4c81c23683 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/ad388202629a0b4afac9af174e88b148dfc76da5 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/4b984fb79d392e7513be7246802285382b685083 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/task.o: task.c  .generated_files/flags/default/afc410ec2e251fb27c5eb64b04a9728027a196c8 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/task.o.d 
	@${RM} ${OBJECTDIR}/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/task.o.d" -MT "${OBJECTDIR}/task.o.d" -MT ${OBJECTDIR}/task.o -o ${OBJECTDIR}/task.o task.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/a58f27c1b9fe61538f735e44f26b4f47599d5455 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/8bc8ac9aa2d2f90e6992dcf0f779f13cffa5e19f .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/d961c4ff1d47f10c9e41ffffff0e0fdbae7805fd .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/9a64aa44a05008bab07387bdbdcd7f787826dec8 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/45d1775b5e501ab2d6e9ee38b1c88f73b12c9826 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/9d8b81f1996775da60f380fcc51bf79ed6482228 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/4d2d46f32a9e4204ec40ae5ac2e2a92430566ab5 .generated_files/flags/default/cf9920e7e9b4455e601e19ce4e4f56686cb22973
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/TEST.X.${IMAGE_TYPE}.hex"
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
