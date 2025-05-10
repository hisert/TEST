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
SOURCEFILES_QUOTED_IF_SPACED=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c register.c PIC_18F67K40.c PIC_18F46K22.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/register.o ${OBJECTDIR}/PIC_18F67K40.o ${OBJECTDIR}/PIC_18F46K22.o
POSSIBLE_DEPFILES=${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/ssd1306_oled.o.d ${OBJECTDIR}/input_debounce.o.d ${OBJECTDIR}/buton_debounce.o.d ${OBJECTDIR}/thread.o.d ${OBJECTDIR}/soft_i2c.o.d ${OBJECTDIR}/PIC_18F87K22.o.d ${OBJECTDIR}/MENU.o.d ${OBJECTDIR}/ATMEGA_64.o.d ${OBJECTDIR}/ssh1106_oled.o.d ${OBJECTDIR}/ATMEGA_328.o.d ${OBJECTDIR}/AS5600_MAS.o.d ${OBJECTDIR}/ws2812b.o.d ${OBJECTDIR}/eeprom.o.d ${OBJECTDIR}/ATMEGA_88.o.d ${OBJECTDIR}/ATMEGA_8.o.d ${OBJECTDIR}/register.o.d ${OBJECTDIR}/PIC_18F67K40.o.d ${OBJECTDIR}/PIC_18F46K22.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/register.o ${OBJECTDIR}/PIC_18F67K40.o ${OBJECTDIR}/PIC_18F46K22.o

# Source Files
SOURCEFILES=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c register.c PIC_18F67K40.c PIC_18F46K22.c



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

MP_PROCESSOR_OPTION=ATmega8
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/fcd621665674f096317ef921198b97cfc9a07ef .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/140a4cd4ac2ef91fd4312e801f2304b05dca7bcb .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/7511759b83202325bda4ea3feddb95f9c9d6a42a .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/f806385b58cbb4e08bb046411fafb5ce70c77b11 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/3eef9f52eba9568e23e0240c1c9911922c37f10c .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/977a854219c26ae1601b84acb00d8540e1b4c17e .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/88726dd8ba42a88d98a7c9df3384fd61674aa7da .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/91039298cc7487919f078275049c95a5a7b4af8b .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/75661ceb8851814215b6506ea6d5b92442704d98 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/72142a4ac9244df7e7ce9529e67679251e5dea47 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/a023cdbb8ce051b3b9ec292156979fd823d49892 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/8fa33adde699032a2c16c4e1b48e49114f1922f0 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/9663c56cb0520e6a449ad14b96a808efdf7f487b .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/e21b017ee4a60a7efe0b4bededb05a7be6db478b .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/abcfdaecb717cac4cb133438722df16012702b92 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/71d849d157f0d886c8aa21cece90f210d6f89c6c .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/1eb99093663397507d33e58722ea2950f19f9101 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
${OBJECTDIR}/PIC_18F67K40.o: PIC_18F67K40.c  .generated_files/flags/default/bfb5bb4c6cc1ae279db1d0fb30ea81f0b1ff6c26 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F67K40.o.d" -MT "${OBJECTDIR}/PIC_18F67K40.o.d" -MT ${OBJECTDIR}/PIC_18F67K40.o -o ${OBJECTDIR}/PIC_18F67K40.o PIC_18F67K40.c 
	
${OBJECTDIR}/PIC_18F46K22.o: PIC_18F46K22.c  .generated_files/flags/default/22f65866433bdb845031495a6371ea5a6e87a2fd .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F46K22.o.d" -MT "${OBJECTDIR}/PIC_18F46K22.o.d" -MT ${OBJECTDIR}/PIC_18F46K22.o -o ${OBJECTDIR}/PIC_18F46K22.o PIC_18F46K22.c 
	
else
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/80decefe8d475710d007fc3b0b7c13becfecb3c4 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/8551114aa03a3c55d9553905250e4a6acc7b59eb .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/f2e959c5d433108354ee9da1a38285400e35b9a9 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/aee6499501cdfeba54144054bdce6a01a56b2874 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/87a6644337ec92d73218d2a661cd4c646c9ecac1 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/a971e48389fc54e143f057268d3373170a03b272 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/39d8f3197ada7fe1d6165c25b213f961542d64cc .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/92296997a46e2959f90c4c5dcf800ffccd3e32ef .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/466c35057afee95b0b8a2948254657e9674e84c8 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/1914e6b522a2c773bfba2b116dfc2d8437762137 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/90bf1194541379fbe3bba6f13e15a211ae5f5b86 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/b7ea7deb3d6a7ef0eee371e33e2d673bc1cec388 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/4060a655f48e551f086a0cff87f62441de124a18 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/2d0144f829d96c76f48dd4e41eaf7646ef0db626 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/788effe463ff917fb6106b86e64a5231141467e .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/2d3c7203dfb8b4edc7a2d08e4e1642f85bd83278 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/ce328c07632e35c97253c026fa9374bc875e5fe7 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
${OBJECTDIR}/PIC_18F67K40.o: PIC_18F67K40.c  .generated_files/flags/default/4df01c22a17903fb94ea7caabf4e04f0304b3e89 .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F67K40.o.d" -MT "${OBJECTDIR}/PIC_18F67K40.o.d" -MT ${OBJECTDIR}/PIC_18F67K40.o -o ${OBJECTDIR}/PIC_18F67K40.o PIC_18F67K40.c 
	
${OBJECTDIR}/PIC_18F46K22.o: PIC_18F46K22.c  .generated_files/flags/default/880f79f646551a15ec6b356308389c2357b3ccec .generated_files/flags/default/ff5a0e252e976dfc10d413cf45d9307cbb73cd0f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F46K22.o.d" -MT "${OBJECTDIR}/PIC_18F46K22.o.d" -MT ${OBJECTDIR}/PIC_18F46K22.o -o ${OBJECTDIR}/PIC_18F46K22.o PIC_18F46K22.c 
	
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
