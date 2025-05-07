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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c task.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c time_out.c register.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/task.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/time_out.o ${OBJECTDIR}/register.o
POSSIBLE_DEPFILES=${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/ssd1306_oled.o.d ${OBJECTDIR}/input_debounce.o.d ${OBJECTDIR}/buton_debounce.o.d ${OBJECTDIR}/thread.o.d ${OBJECTDIR}/soft_i2c.o.d ${OBJECTDIR}/PIC_18F87K22.o.d ${OBJECTDIR}/task.o.d ${OBJECTDIR}/MENU.o.d ${OBJECTDIR}/ATMEGA_64.o.d ${OBJECTDIR}/ssh1106_oled.o.d ${OBJECTDIR}/ATMEGA_328.o.d ${OBJECTDIR}/AS5600_MAS.o.d ${OBJECTDIR}/ws2812b.o.d ${OBJECTDIR}/eeprom.o.d ${OBJECTDIR}/ATMEGA_88.o.d ${OBJECTDIR}/ATMEGA_8.o.d ${OBJECTDIR}/time_out.o.d ${OBJECTDIR}/register.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/task.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/time_out.o ${OBJECTDIR}/register.o

# Source Files
SOURCEFILES=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c task.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c time_out.c register.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/a653c307c16c2a3ca3e5a5fa504979c3475b6fea .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/64eab301af75d578c74ec83259c7c75126d1006c .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/d62d0eeb234cf83ae64e3d19238218effcc44e12 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/9063995d0267234dd0a2188765bc2c25c85cf526 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/134caf06518ec6f70760b6615a80084c11cd3fa5 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/f97bf75276d3ca09dce0e0aaca0f018ceca820ec .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/24717a3af5fb0e2f2cc4565c2c742501e7f1a695 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/task.o: task.c  .generated_files/flags/default/85062aa1079cc88d4c650c89ed1a6dc6422e8d71 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/task.o.d 
	@${RM} ${OBJECTDIR}/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/task.o.d" -MT "${OBJECTDIR}/task.o.d" -MT ${OBJECTDIR}/task.o -o ${OBJECTDIR}/task.o task.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/dcbfd75a91fec86e161bc9ead6f1303520ef8f1a .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/1495f605c154763492f8308486db0345bec62e99 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/28d0716860c5f2a9d0ba827228363597db57d813 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/9e99e32f597c24a86ae340643c881ce132d3e7f1 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/70f0edd40b0424f504276a73ba4655a74d657acd .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/a9bdb70bc32b74e4f5b9dbf85d85c8ed0aab2c13 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/e4f8c816bb282dfcd6a35a5c902db2919a675e87 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/ba07446b4675b2e9ec6f285e953506ce69e67c61 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/42207ab14057af26a4aece26a21c41785d1147a8 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/time_out.o: time_out.c  .generated_files/flags/default/344f733b46432e68a382072c396599e23caf778d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/time_out.o.d 
	@${RM} ${OBJECTDIR}/time_out.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/time_out.o.d" -MT "${OBJECTDIR}/time_out.o.d" -MT ${OBJECTDIR}/time_out.o -o ${OBJECTDIR}/time_out.o time_out.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/b89b578cc162692ea7dc0ed66474cdecc38f28d5 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
else
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/509dd139db1aa1bb7b3ee69270b320c554651b05 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/7bfe63b1549a7293c835af26157bca987e82532e .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/6af85c117ed99c64859d13999439a8849cbae0d3 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/8f63ba66fdbc5ef528074104c53bde9fc17f1916 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/629321f7bf6cabe8903c2f5a6a5d60f02ab723d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/4168ad30400e6753207c2344f18275fceba65008 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/46c1296d7f5524fcfce2d949e38a37c981c9a1dc .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/task.o: task.c  .generated_files/flags/default/8e59efe57f939787288a07ca7e017801f07c1913 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/task.o.d 
	@${RM} ${OBJECTDIR}/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/task.o.d" -MT "${OBJECTDIR}/task.o.d" -MT ${OBJECTDIR}/task.o -o ${OBJECTDIR}/task.o task.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/6e34c96a81d14d9ac515eb99a3855b3916b345e7 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/3ad759481bba098adae96bb29894653057a176a1 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/c51ec652b9a6210f937b78b0ba2c6afda47023a2 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/3fc780d8bf3579228bcfa3d75c21a05679dfd412 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/6b23a1db665ca960d34eb9fad6f2ae2fb28d5192 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/c7d3ccc07ab8e275998a9828671371dc17da7f32 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/7ce38715565ab6b44021da603799973f0b66659 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/fdf9059d2540cca8054063ddf9c9eb76cf30a32d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/8bca6d0ca1d8839f524331aeca9b5e67ca540a2f .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/time_out.o: time_out.c  .generated_files/flags/default/3baf90272410b54a5e57f197dcfbcadabe558351 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/time_out.o.d 
	@${RM} ${OBJECTDIR}/time_out.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/time_out.o.d" -MT "${OBJECTDIR}/time_out.o.d" -MT ${OBJECTDIR}/time_out.o -o ${OBJECTDIR}/time_out.o time_out.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/d1030219d1ee974ef6d8f8353719aca8ea36bb08 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/TEST.${IMAGE_TYPE}.hex"
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
