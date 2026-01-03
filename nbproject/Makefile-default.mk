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
SOURCEFILES_QUOTED_IF_SPACED=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c register.c PIC_18F67K40.c PIC_18F46K22.c lcd_16x2.c ds1307.c lc_512.c hc595.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/register.o ${OBJECTDIR}/PIC_18F67K40.o ${OBJECTDIR}/PIC_18F46K22.o ${OBJECTDIR}/lcd_16x2.o ${OBJECTDIR}/ds1307.o ${OBJECTDIR}/lc_512.o ${OBJECTDIR}/hc595.o
POSSIBLE_DEPFILES=${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/ssd1306_oled.o.d ${OBJECTDIR}/input_debounce.o.d ${OBJECTDIR}/buton_debounce.o.d ${OBJECTDIR}/thread.o.d ${OBJECTDIR}/soft_i2c.o.d ${OBJECTDIR}/PIC_18F87K22.o.d ${OBJECTDIR}/MENU.o.d ${OBJECTDIR}/ATMEGA_64.o.d ${OBJECTDIR}/ssh1106_oled.o.d ${OBJECTDIR}/ATMEGA_328.o.d ${OBJECTDIR}/AS5600_MAS.o.d ${OBJECTDIR}/ws2812b.o.d ${OBJECTDIR}/eeprom.o.d ${OBJECTDIR}/ATMEGA_88.o.d ${OBJECTDIR}/ATMEGA_8.o.d ${OBJECTDIR}/register.o.d ${OBJECTDIR}/PIC_18F67K40.o.d ${OBJECTDIR}/PIC_18F46K22.o.d ${OBJECTDIR}/lcd_16x2.o.d ${OBJECTDIR}/ds1307.o.d ${OBJECTDIR}/lc_512.o.d ${OBJECTDIR}/hc595.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/newmain.o ${OBJECTDIR}/ssd1306_oled.o ${OBJECTDIR}/input_debounce.o ${OBJECTDIR}/buton_debounce.o ${OBJECTDIR}/thread.o ${OBJECTDIR}/soft_i2c.o ${OBJECTDIR}/PIC_18F87K22.o ${OBJECTDIR}/MENU.o ${OBJECTDIR}/ATMEGA_64.o ${OBJECTDIR}/ssh1106_oled.o ${OBJECTDIR}/ATMEGA_328.o ${OBJECTDIR}/AS5600_MAS.o ${OBJECTDIR}/ws2812b.o ${OBJECTDIR}/eeprom.o ${OBJECTDIR}/ATMEGA_88.o ${OBJECTDIR}/ATMEGA_8.o ${OBJECTDIR}/register.o ${OBJECTDIR}/PIC_18F67K40.o ${OBJECTDIR}/PIC_18F46K22.o ${OBJECTDIR}/lcd_16x2.o ${OBJECTDIR}/ds1307.o ${OBJECTDIR}/lc_512.o ${OBJECTDIR}/hc595.o

# Source Files
SOURCEFILES=newmain.c ssd1306_oled.c input_debounce.c buton_debounce.c thread.c soft_i2c.c PIC_18F87K22.c MENU.c ATMEGA_64.c ssh1106_oled.c ATMEGA_328.c AS5600_MAS.c ws2812b.c eeprom.c ATMEGA_88.c ATMEGA_8.c register.c PIC_18F67K40.c PIC_18F46K22.c lcd_16x2.c ds1307.c lc_512.c hc595.c



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

MP_PROCESSOR_OPTION=ATmega64
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/5f1748a124d59b24d9bf30d43645ceba5f5b7c12 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/525830443b7c2be0c88f99008b282ae35cdc0dfd .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/279f4a6e59208ffbc5cca240d6c8d5d8fe66798 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/7ff348814ae1e374985df4b56dd223ea716189ec .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/a3637678accdb05f9161912541b9d8f95b7d7fb7 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/84863605cfd8e08dc6e76a3344726b09ea7d3204 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/88c7ceb6cb549f2533fb305461246bc759d2d378 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/78879a0272fe3135fdfcd0b1e8cfd85586702f80 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/a2ae8882d46a6b07a89138ad31f6fb4beaad3a53 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/51fa019b01aeca35a843b24ef8786124148cbd3b .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/9413c1fa5e83800259035088886066135a454afa .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/6c4be49eed9d4ee24b0f18c99c54f8673aaf6271 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/380e3a6b49dcb0f9c059444773c7b2ec0f0f7db7 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/11db797ee136e7112956fcf729cdadf84872f892 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/d9fd672114ddfcc48e6e13956dceb96d4df4c991 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/1ecc09868d62ab82298a40614d39aebb6c22b78d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/be3bc6723d9502b3abd52c93971bd1eba71c76ee .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
${OBJECTDIR}/PIC_18F67K40.o: PIC_18F67K40.c  .generated_files/flags/default/a1916132146e186e5f365fe8a8051d00a60a2037 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F67K40.o.d" -MT "${OBJECTDIR}/PIC_18F67K40.o.d" -MT ${OBJECTDIR}/PIC_18F67K40.o -o ${OBJECTDIR}/PIC_18F67K40.o PIC_18F67K40.c 
	
${OBJECTDIR}/PIC_18F46K22.o: PIC_18F46K22.c  .generated_files/flags/default/b1b41f504393d3b1f37e5c019986ad81a53371cf .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F46K22.o.d" -MT "${OBJECTDIR}/PIC_18F46K22.o.d" -MT ${OBJECTDIR}/PIC_18F46K22.o -o ${OBJECTDIR}/PIC_18F46K22.o PIC_18F46K22.c 
	
${OBJECTDIR}/lcd_16x2.o: lcd_16x2.c  .generated_files/flags/default/b4ba88445eda03e1fa54a4927d7f93850866fb0d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd_16x2.o.d 
	@${RM} ${OBJECTDIR}/lcd_16x2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd_16x2.o.d" -MT "${OBJECTDIR}/lcd_16x2.o.d" -MT ${OBJECTDIR}/lcd_16x2.o -o ${OBJECTDIR}/lcd_16x2.o lcd_16x2.c 
	
${OBJECTDIR}/ds1307.o: ds1307.c  .generated_files/flags/default/204a343a655842de1c73d21596610e5fbeb74e92 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds1307.o.d 
	@${RM} ${OBJECTDIR}/ds1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ds1307.o.d" -MT "${OBJECTDIR}/ds1307.o.d" -MT ${OBJECTDIR}/ds1307.o -o ${OBJECTDIR}/ds1307.o ds1307.c 
	
${OBJECTDIR}/lc_512.o: lc_512.c  .generated_files/flags/default/1bde54bde19323c6f65187cbeef4b7350051a327 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lc_512.o.d 
	@${RM} ${OBJECTDIR}/lc_512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lc_512.o.d" -MT "${OBJECTDIR}/lc_512.o.d" -MT ${OBJECTDIR}/lc_512.o -o ${OBJECTDIR}/lc_512.o lc_512.c 
	
${OBJECTDIR}/hc595.o: hc595.c  .generated_files/flags/default/cad4a9712af45c5a7e2fdb2c46a5eb1b8ad22cbd .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hc595.o.d 
	@${RM} ${OBJECTDIR}/hc595.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/hc595.o.d" -MT "${OBJECTDIR}/hc595.o.d" -MT ${OBJECTDIR}/hc595.o -o ${OBJECTDIR}/hc595.o hc595.c 
	
else
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/c24d4367fba870c3166a07eb7f24ba238bb0a488 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newmain.o.d" -MT "${OBJECTDIR}/newmain.o.d" -MT ${OBJECTDIR}/newmain.o -o ${OBJECTDIR}/newmain.o newmain.c 
	
${OBJECTDIR}/ssd1306_oled.o: ssd1306_oled.c  .generated_files/flags/default/ec10459035ac461f18925d0b2a08edd71220b781 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o.d 
	@${RM} ${OBJECTDIR}/ssd1306_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssd1306_oled.o.d" -MT "${OBJECTDIR}/ssd1306_oled.o.d" -MT ${OBJECTDIR}/ssd1306_oled.o -o ${OBJECTDIR}/ssd1306_oled.o ssd1306_oled.c 
	
${OBJECTDIR}/input_debounce.o: input_debounce.c  .generated_files/flags/default/5914530726fede0504ec76f587d9f39dde6fa1f .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/input_debounce.o.d 
	@${RM} ${OBJECTDIR}/input_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/input_debounce.o.d" -MT "${OBJECTDIR}/input_debounce.o.d" -MT ${OBJECTDIR}/input_debounce.o -o ${OBJECTDIR}/input_debounce.o input_debounce.c 
	
${OBJECTDIR}/buton_debounce.o: buton_debounce.c  .generated_files/flags/default/1befe437cf24ccd4d76f25b81cecd17d2368bf78 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buton_debounce.o.d 
	@${RM} ${OBJECTDIR}/buton_debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buton_debounce.o.d" -MT "${OBJECTDIR}/buton_debounce.o.d" -MT ${OBJECTDIR}/buton_debounce.o -o ${OBJECTDIR}/buton_debounce.o buton_debounce.c 
	
${OBJECTDIR}/thread.o: thread.c  .generated_files/flags/default/cbf519561269fd5b7d9a1f62eebcb8d66010d26d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/thread.o.d 
	@${RM} ${OBJECTDIR}/thread.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/thread.o.d" -MT "${OBJECTDIR}/thread.o.d" -MT ${OBJECTDIR}/thread.o -o ${OBJECTDIR}/thread.o thread.c 
	
${OBJECTDIR}/soft_i2c.o: soft_i2c.c  .generated_files/flags/default/8929c38bcaccba895bc2a8b15d9fb88f1afc0998 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/soft_i2c.o.d 
	@${RM} ${OBJECTDIR}/soft_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/soft_i2c.o.d" -MT "${OBJECTDIR}/soft_i2c.o.d" -MT ${OBJECTDIR}/soft_i2c.o -o ${OBJECTDIR}/soft_i2c.o soft_i2c.c 
	
${OBJECTDIR}/PIC_18F87K22.o: PIC_18F87K22.c  .generated_files/flags/default/6d14fbbca21a4c862256ebf3149b34a1f8b403c5 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F87K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F87K22.o.d" -MT "${OBJECTDIR}/PIC_18F87K22.o.d" -MT ${OBJECTDIR}/PIC_18F87K22.o -o ${OBJECTDIR}/PIC_18F87K22.o PIC_18F87K22.c 
	
${OBJECTDIR}/MENU.o: MENU.c  .generated_files/flags/default/bac7cb02d583ddcf92d392da25ca8eb354bdc9af .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MENU.o.d 
	@${RM} ${OBJECTDIR}/MENU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/MENU.o.d" -MT "${OBJECTDIR}/MENU.o.d" -MT ${OBJECTDIR}/MENU.o -o ${OBJECTDIR}/MENU.o MENU.c 
	
${OBJECTDIR}/ATMEGA_64.o: ATMEGA_64.c  .generated_files/flags/default/10d8516169723603ae08ae0dd996471309badb75 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_64.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_64.o.d" -MT "${OBJECTDIR}/ATMEGA_64.o.d" -MT ${OBJECTDIR}/ATMEGA_64.o -o ${OBJECTDIR}/ATMEGA_64.o ATMEGA_64.c 
	
${OBJECTDIR}/ssh1106_oled.o: ssh1106_oled.c  .generated_files/flags/default/5871b3689628d7ad2d2a6c44cb0aa150c85fee0f .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o.d 
	@${RM} ${OBJECTDIR}/ssh1106_oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ssh1106_oled.o.d" -MT "${OBJECTDIR}/ssh1106_oled.o.d" -MT ${OBJECTDIR}/ssh1106_oled.o -o ${OBJECTDIR}/ssh1106_oled.o ssh1106_oled.c 
	
${OBJECTDIR}/ATMEGA_328.o: ATMEGA_328.c  .generated_files/flags/default/b489ff495c837b7f39291fd56c0d50a7892db25d .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_328.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_328.o.d" -MT "${OBJECTDIR}/ATMEGA_328.o.d" -MT ${OBJECTDIR}/ATMEGA_328.o -o ${OBJECTDIR}/ATMEGA_328.o ATMEGA_328.c 
	
${OBJECTDIR}/AS5600_MAS.o: AS5600_MAS.c  .generated_files/flags/default/184f549d74cbcb314d5df3c5ac12e24d740022f3 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o.d 
	@${RM} ${OBJECTDIR}/AS5600_MAS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/AS5600_MAS.o.d" -MT "${OBJECTDIR}/AS5600_MAS.o.d" -MT ${OBJECTDIR}/AS5600_MAS.o -o ${OBJECTDIR}/AS5600_MAS.o AS5600_MAS.c 
	
${OBJECTDIR}/ws2812b.o: ws2812b.c  .generated_files/flags/default/9a159b4b87d126ae22bfb6b0986e5aec11f09555 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812b.o.d 
	@${RM} ${OBJECTDIR}/ws2812b.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ws2812b.o.d" -MT "${OBJECTDIR}/ws2812b.o.d" -MT ${OBJECTDIR}/ws2812b.o -o ${OBJECTDIR}/ws2812b.o ws2812b.c 
	
${OBJECTDIR}/eeprom.o: eeprom.c  .generated_files/flags/default/544f08c4198b7ac36dd19be526e89aeecd3fe643 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.o.d 
	@${RM} ${OBJECTDIR}/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/eeprom.o.d" -MT "${OBJECTDIR}/eeprom.o.d" -MT ${OBJECTDIR}/eeprom.o -o ${OBJECTDIR}/eeprom.o eeprom.c 
	
${OBJECTDIR}/ATMEGA_88.o: ATMEGA_88.c  .generated_files/flags/default/5a20ab066e6bd8539e08f423c557ebebbb3b9f7b .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_88.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_88.o.d" -MT "${OBJECTDIR}/ATMEGA_88.o.d" -MT ${OBJECTDIR}/ATMEGA_88.o -o ${OBJECTDIR}/ATMEGA_88.o ATMEGA_88.c 
	
${OBJECTDIR}/ATMEGA_8.o: ATMEGA_8.c  .generated_files/flags/default/f62a940d4f5ceab33a628b74f4c97faf299276ce .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o.d 
	@${RM} ${OBJECTDIR}/ATMEGA_8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ATMEGA_8.o.d" -MT "${OBJECTDIR}/ATMEGA_8.o.d" -MT ${OBJECTDIR}/ATMEGA_8.o -o ${OBJECTDIR}/ATMEGA_8.o ATMEGA_8.c 
	
${OBJECTDIR}/register.o: register.c  .generated_files/flags/default/36d0840cd4105bc96db4df49ee2cd0b926e4a6a .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/register.o.d 
	@${RM} ${OBJECTDIR}/register.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/register.o.d" -MT "${OBJECTDIR}/register.o.d" -MT ${OBJECTDIR}/register.o -o ${OBJECTDIR}/register.o register.c 
	
${OBJECTDIR}/PIC_18F67K40.o: PIC_18F67K40.c  .generated_files/flags/default/c8f71230af2740121b0e97b9cdcc6ed085e536f6 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F67K40.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F67K40.o.d" -MT "${OBJECTDIR}/PIC_18F67K40.o.d" -MT ${OBJECTDIR}/PIC_18F67K40.o -o ${OBJECTDIR}/PIC_18F67K40.o PIC_18F67K40.c 
	
${OBJECTDIR}/PIC_18F46K22.o: PIC_18F46K22.c  .generated_files/flags/default/cd508f3449019f41e95adfe9e4dd2d47f18a2912 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o.d 
	@${RM} ${OBJECTDIR}/PIC_18F46K22.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/PIC_18F46K22.o.d" -MT "${OBJECTDIR}/PIC_18F46K22.o.d" -MT ${OBJECTDIR}/PIC_18F46K22.o -o ${OBJECTDIR}/PIC_18F46K22.o PIC_18F46K22.c 
	
${OBJECTDIR}/lcd_16x2.o: lcd_16x2.c  .generated_files/flags/default/b5bbd75d981c7f5cdcd665bc997d5a4a2dc5d457 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd_16x2.o.d 
	@${RM} ${OBJECTDIR}/lcd_16x2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd_16x2.o.d" -MT "${OBJECTDIR}/lcd_16x2.o.d" -MT ${OBJECTDIR}/lcd_16x2.o -o ${OBJECTDIR}/lcd_16x2.o lcd_16x2.c 
	
${OBJECTDIR}/ds1307.o: ds1307.c  .generated_files/flags/default/bb79395f3ff849c9eb060bc5e070a53e3cb192da .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds1307.o.d 
	@${RM} ${OBJECTDIR}/ds1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ds1307.o.d" -MT "${OBJECTDIR}/ds1307.o.d" -MT ${OBJECTDIR}/ds1307.o -o ${OBJECTDIR}/ds1307.o ds1307.c 
	
${OBJECTDIR}/lc_512.o: lc_512.c  .generated_files/flags/default/895e72e561d8e096b571aa96d197e69f167e7f5a .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lc_512.o.d 
	@${RM} ${OBJECTDIR}/lc_512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lc_512.o.d" -MT "${OBJECTDIR}/lc_512.o.d" -MT ${OBJECTDIR}/lc_512.o -o ${OBJECTDIR}/lc_512.o lc_512.c 
	
${OBJECTDIR}/hc595.o: hc595.c  .generated_files/flags/default/bd45d1349035742aa1d5b5dc93eee126aef12052 .generated_files/flags/default/5ce8b7afcd8d2fec01fc08912832efc321890592
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hc595.o.d 
	@${RM} ${OBJECTDIR}/hc595.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/hc595.o.d" -MT "${OBJECTDIR}/hc595.o.d" -MT ${OBJECTDIR}/hc595.o -o ${OBJECTDIR}/hc595.o hc595.c 
	
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
