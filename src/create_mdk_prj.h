void Set_MDK_stm32f103c8( wxString *buf, wxString prj_name )
{
	*buf = wxEmptyString;
	buf->Append( wxT( "### uVision2 Project, (C) Keil Software\r\n" ) );
	buf->Append( wxT( "### Do not modify !\r\n" ) );
	buf->Append( wxT( "\r\n" ) );
	buf->Append( wxT( "Target (" ) + prj_name.Upper() + wxT( "), 0x0004 // Tools: 'ARM-ADS'\r\n" ) );
	buf->Append( wxT( "\r\n" ) );
	buf->Append( wxT( "Group (StartUp)\r\n" ) );
	buf->Append( wxT( "Group (CMSIS)\r\n" ) );
	buf->Append( wxT( "Group (USB)\r\n" ) );
	buf->Append( wxT( "Group (SPL)\r\n" ) );
	buf->Append( wxT( "Group (Source Files)\r\n" ) );
	buf->Append( wxT( "\r\n" ) );
	buf->Append( wxT( "File 1,2,<.\\main\\start_mdk\\startup_stm32f10x_md.s><startup_stm32f10x_md.s>\r\n" ) );
	buf->Append( wxT( "File 2,5,<.\\cmsis_mdk\\stm32f10x.h><stm32f10x.h>\r\n" ) );
	buf->Append( wxT( "File 2,5,<.\\spl\\inc_mdk\\stm32f10x_conf.h><stm32f10x_conf.h>\r\n" ) );
	buf->Append( wxT( "File 2,1,<.\\cmsis_mdk\\core_cm3.c><core_cm3.c>\r\n" ) );
	buf->Append( wxT( "File 2,1,<.\\cmsis_mdk\\system_stm32f10x.c><system_stm32f10x.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\hw_config.c><hw_config.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\usb_pwr.c><usb_pwr.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\stm32_it.c><stm32_it.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\usb_prop.c><usb_prop.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\usb_istr.c><usb_istr.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\src\\usb_desc.c><usb_desc.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_core.c><usb_core.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_init.c><usb_init.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_int.c><usb_int.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_mem.c><usb_mem.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_regs.c><usb_regs.c>\r\n" ) );
	buf->Append( wxT( "File 3,1,<.\\usb\\usb_fs\\src\\usb_sil.c><usb_sil.c>\r\n" ) );
	buf->Append( wxT( "File 4,1,<.\\spl\\src\\stm32f10x_rcc.c><stm32f10x_rcc.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\main\\main.c><main.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_gpio.c><stm32f10x_gpio.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_usart.c><stm32f10x_usart.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\misc.c><misc.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_tim.c><stm32f10x_tim.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_spi.c><stm32f10x_spi.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_iwdg.c><stm32f10x_iwdg.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_exti.c><stm32f10x_exti.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_adc.c><stm32f10x_adc.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_dac.c><stm32f10x_dac.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_i2c.c><stm32f10x_i2c.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_dma.c><stm32f10x_dma.c>\r\n" ) );
	buf->Append( wxT( "File 5,1,<.\\spl\\src\\stm32f10x_flash.c><stm32f10x_flash.c>\r\n" ) );
	buf->Append( wxT( "\r\n" ) );
	buf->Append( wxT( "\r\n" ) );
	buf->Append( wxT( "Options 1,0,0  // Target '" ) + prj_name.Upper() + wxT( "'\r\n" ) );
	if( PRJ_MCU == wxT( "STM32F103CBT6" ) )
	{
		buf->Append( wxT( " Device (STM32F103CB)\r\n" ) );
	}
	else
	{
		buf->Append( wxT( " Device (STM32F103C8)\r\n" ) );
	}
	buf->Append( wxT( " Vendor (STMicroelectronics)\r\n" ) );
	buf->Append( wxT( " Cpu (IRAM(0x20000000-0x20004FFF) IROM(0x8000000-0x800FFFF) CLOCK(8000000) CPUTYPE(\"Cortex-M3\"))\r\n" ) );
	buf->Append( wxT( " FlashUt ()\r\n" ) );
	buf->Append( wxT( " StupF (\"STARTUP\\ST\\STM32F10x\\startup_stm32f10x_md.s\" (\"STM32 Medium Density Line Startup Code\"))\r\n" ) );
	if( PRJ_MCU == wxT( "STM32F103CBT6" ) )
	{
		buf->Append( wxT( " FlashDR (UL2CM3(-O14 -S0 -C0 -N00(\"ARM Cortex-M3\") -D00(1BA00477) -L00(4) -FO7 -FD20000000 -FC800 -FN1 -FF0STM32F10x_128 -FS08000000 -FL020000))\r\n" ) );
	}
	else
	{
		buf->Append( wxT( " FlashDR (UL2CM3(-O14 -S0 -C0 -N00(\"ARM Cortex-M3\") -D00(1BA00477) -L00(4) -FO7 -FD20000000 -FC800 -FN1 -FF0STM32F10x_128 -FS08000000 -FL010000))\r\n" ) );
	}
	buf->Append( wxT( " DevID (4235)\r\n" ) );
	buf->Append( wxT( " Rgf (stm32f10x.h)\r\n" ) );
	buf->Append( wxT( " Mem ()\r\n" ) );
	buf->Append( wxT( " C ()\r\n" ) );
	buf->Append( wxT( " A ()\r\n" ) );
	buf->Append( wxT( " RL ()\r\n" ) );
	buf->Append( wxT( " OH ()\r\n" ) );
	buf->Append( wxT( " DBC_IFX ()\r\n" ) );
	buf->Append( wxT( " DBC_CMS ()\r\n" ) );
	buf->Append( wxT( " DBC_AMS ()\r\n" ) );
	buf->Append( wxT( " DBC_LMS ()\r\n" ) );
	buf->Append( wxT( " UseEnv=0\r\n" ) );
	buf->Append( wxT( " EnvBin ()\r\n" ) );
	buf->Append( wxT( " EnvInc ()\r\n" ) );
	buf->Append( wxT( " EnvLib ()\r\n" ) );
	buf->Append( wxT( " EnvReg (ST\\STM32F10x\\)\r\n" ) );
	buf->Append( wxT( " OrgReg (ST\\STM32F10x\\)\r\n" ) );
	buf->Append( wxT( " TgStat=16\r\n" ) );
	buf->Append( wxT( " OutDir (.\\bin\\)\r\n" ) );
	buf->Append( wxT( " OutName (..\\" ) + prj_name + wxT( ")\r\n" ) );
	buf->Append( wxT( " GenApp=1\r\n" ) );
	buf->Append( wxT( " GenLib=0\r\n" ) );
	buf->Append( wxT( " GenHex=0\r\n" ) );
	buf->Append( wxT( " Debug=0\r\n" ) );
	buf->Append( wxT( " Browse=0\r\n" ) );
	buf->Append( wxT( " LstDir (.\\lst\\)\r\n" ) );
	buf->Append( wxT( " HexSel=1\r\n" ) );
	buf->Append( wxT( " MG32K=0\r\n" ) );
	buf->Append( wxT( " TGMORE=0\r\n" ) );
	buf->Append( wxT( " RunUsr 0 0 <>\r\n" ) );
	buf->Append( wxT( " RunUsr 1 0 <>\r\n" ) );
	buf->Append( wxT( " BrunUsr 0 0 <>\r\n" ) );
	buf->Append( wxT( " BrunUsr 1 0 <>\r\n" ) );
	buf->Append( wxT( " CrunUsr 0 0 <>\r\n" ) );
	buf->Append( wxT( " CrunUsr 1 0 <>\r\n" ) );
	buf->Append( wxT( " SVCSID <>\r\n" ) );
	buf->Append( wxT( " GLFLAGS=1790\r\n" ) );
	buf->Append( wxT( " ADSFLGA { 226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " ACPUTYP (\"Cortex-M3\")\r\n" ) );
	buf->Append( wxT( " RVDEV ()\r\n" ) );
	buf->Append( wxT( " ADSTFLGA { 0,12,0,2,99,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " OCMADSOCM { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " OCMADSIRAM { 0,0,0,0,32,0,80,0,0 }\r\n" ) );
	buf->Append( wxT( " OCMADSIROM { 1,0,0,0,8,0,0,1,0 }\r\n" ) );
	buf->Append( wxT( " OCMADSXRAM { 0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " OCR_RVCT { 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,8,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,80,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " RV_STAVEC ()\r\n" ) );
	buf->Append( wxT( " ADSCCFLG { 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " ADSCMISC ()\r\n" ) );
	buf->Append( wxT( " ADSCDEFN (USE_STDPERIPH_DRIVER STM32F10X_MD)\r\n" ) );
	buf->Append( wxT( " ADSCUDEF ()\r\n" ) );
	buf->Append( wxT( " ADSCINCD (.\\cmsis_mdk;.\\spl\\inc_mdk;.\\spl\\inc;.\\spl\\src;.\\main;.\\usb\\inc;.\\usb\\src;.\\usb\\usb_fs\\inc;.\\usb\\usb_fs\\src)\r\n" ) );
	buf->Append( wxT( " ADSASFLG { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " ADSAMISC ()\r\n" ) );
	buf->Append( wxT( " ADSADEFN ()\r\n" ) );
	buf->Append( wxT( " ADSAUDEF ()\r\n" ) );
	buf->Append( wxT( " ADSAINCD ()\r\n" ) );
	buf->Append( wxT( " PropFld { 0,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " IncBld=1\r\n" ) );
	buf->Append( wxT( " AlwaysBuild=0\r\n" ) );
	buf->Append( wxT( " GenAsm=0\r\n" ) );
	buf->Append( wxT( " AsmAsm=0\r\n" ) );
	buf->Append( wxT( " PublicsOnly=0\r\n" ) );
	buf->Append( wxT( " StopCode=3\r\n" ) );
	buf->Append( wxT( " CustArgs ()\r\n" ) );
	buf->Append( wxT( " LibMods ()\r\n" ) );
	buf->Append( wxT( " ADSLDFG { 17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " ADSLDTA (0x08000000)\r\n" ) );
	buf->Append( wxT( " ADSLDDA (0x20000000)\r\n" ) );
	buf->Append( wxT( " ADSLDSC ()\r\n" ) );
	buf->Append( wxT( " ADSLDIB ()\r\n" ) );
	buf->Append( wxT( " ADSLDIC ()\r\n" ) );
	buf->Append( wxT( " ADSLDMC ()\r\n" ) );
	buf->Append( wxT( " ADSLDIF ()\r\n" ) );
	buf->Append( wxT( " ADSLDDW ()\r\n" ) );
	if( PRJ_MCU == wxT( "STM32F103CBT6" ) )
	{
		buf->Append( wxT( "  OPTDL (SARMCM3.DLL)()(DARMSTM.DLL)(-pSTM32F103CB)(SARMCM3.DLL)()(TARMSTM.DLL)(-pSTM32F103CB)\r\n" ) );
	}
	else
	{
		buf->Append( wxT( "  OPTDL (SARMCM3.DLL)()(DARMSTM.DLL)(-pSTM32F103C8)(SARMCM3.DLL)()(TARMSTM.DLL)(-pSTM32F103C8)\r\n" ) );
	}
	buf->Append( wxT( "  OPTDBG 311294,12,()()()()()()()()()() (STLink\\ST-LINKIII-KEIL_SWO.dll)()()()\r\n" ) );
	buf->Append( wxT( " FLASH1 { 25,0,0,0,1,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0 }\r\n" ) );
	buf->Append( wxT( " FLASH2 (BIN\\UL2CM3.DLL)\r\n" ) );
	buf->Append( wxT( " FLASH3 ()\r\n" ) );
	buf->Append( wxT( " FLASH4 ()\r\n" ) );
	buf->Append( wxT( "EndOpt\r\n" ) );
}
