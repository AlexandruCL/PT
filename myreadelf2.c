#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	unsigned char magic;
	unsigned char elf[3];
	unsigned char value;
	unsigned flag;
	if (argc != 2) {
		printf("Wrong number of arguments. Use:\n");
		printf("%s filename.x\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Start processing..\n");

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	if (fread(&magic, 1, 1, fp) != 1) {
		perror("fread()");
		exit(EXIT_FAILURE);
	}

	if (magic == 0x7f) printf("Magic valure for ELF found\n");
	else {
		printf("This seems not to be a valid ELF program\n");
		exit(EXIT_FAILURE);
	}

	if (fread(elf, 3, 1, fp) != 1) {
		perror("fread()\n");
		printf("Line number is %u\n", __LINE__);
		printf("Source code file is %s\n", __FILE__);
		exit(EXIT_FAILURE);
	}

	if ((elf[0] != 'E') || (elf[1] != 'L') || 
	    (elf[2] != 'F')) {
		printf("This is not an ELF file!!\n");
		exit(EXIT_FAILURE);
	} else printf("ELF file found! Printing header:\n");

	if(fread(&value,1,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		switch (value)
		{
			case 0x1: 
				flag=32; printf("%u (bytes into file)\n",flag); break;
			case 0x2: 
				flag=64; printf("%u (bytes into file)\n",flag); break;
		}
	}

	if(fread(&value,1,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		switch (value)
		{
			case 0x1: 
				printf("System is little endian\n");
				break;
			case 0x2: 
				printf("System is big endian\n");
				break;
		}
	}
	

	if(fread(&value,1,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Version: 1(current)\n");
	}

	if(fread(&value,1,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		printf("ABI: ");
		switch (value)
		{
			case 0x00: printf("System V\n");break;
			case 0x01: printf("HP-UX\n");break;
			case 0x02: printf("NETBSD\n");break;
			case 0x03: printf("LINUX\n");break;
			case 0x04: printf("GNU Hurd\n");break;
			case 0x06: printf("Solaris\n");break;
			case 0x07: printf("AIX\n");break;
			case 0x08: printf("IRIX\n");break;
			case 0x09: printf("FreeBSD\n");break;
			case 0x0A: printf("Tru64\n");break;
			case 0x0B: printf("Novell Modesto\n");break;
			case 0x0C: printf("OpenBSD\n");break;
			case 0x0D: printf("OpenVMS\n");break;
			case 0x0E: printf("NonStop Kernel\n");break;
			case 0x0F: printf("AROS\n");break;
			case 0x10: printf("FenixOS\n");break;
			case 0x11: printf("Nyxu CloudABI\n");break;
			case 0x12: printf("Status Technologies OpenVOS\n");break;
	
		}
	}
		if(fread(&value,1,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		printf("ABI Version : %u\n",value);
	}
	unsigned char aux[7];
	unsigned char aux2[2];
		if(fread(aux,7,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
		if(fread(aux2,2,1,fp)!=1)
	{
		printf("File is not correct\n");
		exit(EXIT_FAILURE);
	}
	else{
		switch (*aux2){
			case 0x00: printf("Unknown \n"); break;
			case 0x01: printf("Relocatable file \n"); break;
			case 0x02: printf("Executable file \n"); break;
			case 0x03: printf("Shared object\n"); break;
			case 0x04: printf("Core file\n"); break;
			case 0xFE: printf("Resreved inclusive range. Operating system specific. \n"); break;
			case 0xFF: printf("Reserved inclusive range. Processor specific. \n"); break;
		}
	}
	if(fread(aux2, 2,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
		else{
			switch(*aux2)
			{
				case 0x00: printf("No specific instruction set.\n"); break;
				case 0x01: printf("AT&Y WE 32100\n"); break;
				case 0x02: printf("SPARC\n"); break;
				case 0x03: printf("x86\n"); break;
				case 0x04: printf("Motorola 6800\n"); break;
				case 0x05: printf("Motorola 8800\n"); break;
				case 0x06: printf("Intel MCU\n"); break;
				case 0x07: printf("Intel 80860\n"); break;
				case 0x08: printf("MIPS\n"); break;
				case 0x09: printf("IBM System/370\n"); break;
				case 0x0A: printf("MIPS RS3000 Little endian\n"); break;
				case 0x0B: printf("Reserbed for future use\n"); break;
				case 0x0E: printf("Reserbed for future use\n"); break;
				case 0x0F: printf("Hewlett-Packard PA-RISC\n"); break;
				case 0x13: printf("Intel 80960\n"); break;
				case 0x14: printf("PowerPC\n"); break;
				case 0x15: printf("PowerPC (64 bit)\n"); break;
				case 0x16: printf("S390\n"); break;
				case 0x17: printf("IBM SPU/SPC\n"); break;
				case 0x18: printf("Reserved for future use\n"); break;
				case 0x23: printf("Reserved for future use\n"); break;
				case 0x24: printf("NEC V800\n"); break;
				case 0x25: printf("Fujitsu FR20\n"); break;
				case 0x26: printf("TRW RH-32\n"); break;
				case 0x27: printf("Motorola RCE\n"); break;
				case 0x28: printf("ARM\n"); break;
				case 0x29: printf("Digital alpha\n"); break;
				case 0x2A: printf("SuperH\n"); break;
				case 0x2B: printf("SPARC Versoin 9\n"); break;
				case 0x2C: printf("Siemens TriCore embedded processor\n"); break;
				case 0x2D: printf("Argonaut RISC Core\n"); break;
				case 0x2E: printf("Hitachi H8/300\n"); break;
				case 0x2F: printf("Hitachi H8/300H\n"); break;
				case 0x30: printf("Hitachi H8S\n"); break;
				case 0x31: printf("Hitachi H8/500\n"); break;
				case 0x32: printf("IA-64\n"); break;
				case 0x33: printf("Standford MIPS-X\n"); break;
				case 0x34: printf("Motorola Cold Fire\n"); break;
				case 0x35: printf("Motorola M68Hc12\n"); break;
				case 0x36: printf("Fujitsu MMAA Multimedia Accelerato\n"); break;
				case 0x37: printf("Siemens PCP\n"); break;
				case 0x38: printf("Sony nCPU embedded RISC processor\n"); break;
				case 0x39: printf("Denso NDR1 microprocessor\n"); break;
				case 0x3A: printf("Motorola Star*Core processor\n"); break;
				case 0x3B: printf("Toyota ME16 processor\n"); break;
				case 0x3C: printf("STMicroelectronics ST100 processor\n"); break;
				case 0x3D: printf("Advancedd Logic Corp. TinyJ embedded processor family\n"); break;
				case 0x3E: printf("AMD x86-64\n"); break;
				case 0x3F: printf("Sony dsp Processor\n"); break;
				case 0x40: printf("Digital equipment Corp. PDP-10\n"); break;
				case 0x41: printf("Digital equipment Corp. PDP-11\n"); break;
				case 0x42: printf("Simenes FX66 microcontroller\n"); break;
				case 0x43: printf("STMicroelectronics ST9+ 8/16 bit microcontroller\n"); break;
				case 0x44: printf("STMicroelectronics ST7 8/ bit microcontroller\n"); break;
				case 0x45: printf("Motorola MC68HC16 Microcontroller\n"); break;
				case 0x46: printf("Motorola MC68HC11 Microcontroller\n"); break;
				case 0x47: printf("Motorola MC68HC08 Microcontroller\n"); break;
				case 0x48: printf("Motorola MC68HC05 Microcontroller\n"); break;
				case 0x49: printf("Sillicon Graphics SVx\n"); break;
				case 0x4A: printf("STMicroelectornics ST19 8--bit microcontroller\n"); break;
				case 0x4B: printf("Digital VAX\n"); break;
				case 0x4C: printf("Axis Communicatoin 32-bit embedded processor\n"); break;
				case 0x4D: printf("Infineaon Technologies 32-bit embedded processor\n"); break;
				case 0x4E: printf("Element 14 64-bit DSP processor\n"); break;
				case 0x4F: printf("LSI Logic 16-bit DSP processor\n"); break;
				case 0x8c: printf("TMS320C600 Familt \n"); break;
				case 0xAF: printf("MCST Elbrus e2k \n"); break;
				case 0xB7 : printf("Arm 64-bit \n"); break;
				case 0xDC: printf("Zilog Z800 \n"); break;
				case 0xF3: printf("Risc-V \n"); break;
				case 0xF7: printf("Berkeley Packet Filter \n"); break;
				case 0x10: printf("WDC 65C816 \n"); break;


		}

	}

	unsigned char aux3[4];
	if(fread(aux3, 4, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	if(flag==32)
	{
			if(fread(aux3, 4,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		unsigned char aux4[8];
			if(fread(aux4, 8,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	if(flag==32)
	{
			if(fread(aux3, 4,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		unsigned char aux4[8];
			if(fread(aux4, 8,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	if(flag==32)
	{
			if(fread(aux3, 4,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		unsigned char aux4[8];
			if(fread(aux4, 8,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	}
	if(fread(aux3, 4,1, fp)!=1)
		{
			printf("File is not correct \n");
			exit(EXIT_FAILURE);
		}
	if(fread(aux2, 2, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	if(fread(aux2, 2, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	if(fread(aux2, 2, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	if(fread(aux2, 2, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	if(fread(aux2, 2, 1, fp)!=1)
	{
		printf("File is not correct \n");
		exit(EXIT_FAILURE);
	}
	
	if (fclose(fp) != 0) {
		perror("fclose()");
		exit(EXIT_FAILURE);	
	}
	return 0;
}
