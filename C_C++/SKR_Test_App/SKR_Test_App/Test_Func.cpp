#include "stdafx.h"
#include "Test_Func.h"


using namespace std;

static char IntToHex(unsigned x) {
	x &= 15;
	if (x <= 9) return x + '0';
	return x - 10 + 'A';
}

static int hexToint(unsigned x) {
	if (x <= '9') return x - '0';
	return x + 10 - 'A';
}

void Gen_Incr_num_file(unsigned int size, char* FilePath)
{
	cout << "Gen_Incr_num_file : IN" << endl;

	cout << "Size : " << size << " ||" << " FilePath : " << FilePath << endl;

	FILE* pFile;
	errno_t err;
	unsigned char* rDevBuf = NULL;
	unsigned int numByWrSuccess = 0;
	unsigned int numByToWr = size;
	unsigned int Count = 0;
	unsigned int numByWriteDone = 0;
	unsigned int i = 0;

	err = fopen_s(&pFile, FilePath, "wb");
	rDevBuf = (unsigned char*)malloc(MAX_PKT_SIZE);

	while (numByToWr)
	{
		if (numByToWr > MAX_PKT_SIZE)
			numByToWr = MAX_PKT_SIZE;

		for (i = 0; i < numByToWr / 4; i++)
		{
			rDevBuf[i * 4 + 0] = ((Count >> 24) & 0xFF);
			rDevBuf[i * 4 + 1] = ((Count >> 16) & 0xFF);
			rDevBuf[i * 4 + 2] = ((Count >> 8) & 0xFF);
			rDevBuf[i * 4 + 3] = ((Count >> 0) & 0xFF);
			Count++;
		}
		numByWrSuccess = i * 4;

		if (err)
		{
			numByWrSuccess = 0;
			break;
		}

		numByWriteDone += numByWrSuccess;

		if (numByWriteDone >= size)
		{
			fwrite(rDevBuf, 1, numByToWr, pFile);
			numByWriteDone = size;
			break;
		}
		else
		{
			fwrite(rDevBuf, 1, numByWrSuccess, pFile);
		}

		numByToWr = size - numByWriteDone;
		cout << "numByToWr : " << numByToWr << " ||" << " numByWriteDone : " << numByWriteDone << endl;
	}
	free(rDevBuf);
	fclose(pFile);

	cout << "Gen_Incr_num_file : OUT" << endl;
}

void Gen_Random_num_file(unsigned int size, char* FilePath)
{
	cout << "Gen_Random_num_file : IN" << endl;

	cout << "Size : " << size << " ||" << " FilePath : " << FilePath << endl;

	FILE* pFile;
	errno_t err;
	unsigned char* rDevBuf = NULL;
	unsigned int numByWrSuccess = 0;
	unsigned int numByToWr = size;
	unsigned int numByWriteDone = 0;
	unsigned int i = 0;

	err = fopen_s(&pFile, FilePath, "wb");
	rDevBuf = (unsigned char*)malloc(MAX_PKT_SIZE);

	while (numByToWr)
	{
		if (numByToWr > MAX_PKT_SIZE)
			numByToWr = MAX_PKT_SIZE;

		for (i = 0; i < numByToWr; i++)
		{
			rDevBuf[i] = rand();
		}
		numByWrSuccess = i;

		if (err)
		{
			numByWrSuccess = 0;
			break;
		}

		numByWriteDone += numByWrSuccess;

		if (numByWriteDone >= size)
		{
			fwrite(rDevBuf, 1, numByToWr, pFile);
			numByWriteDone = size;
			break;
		}
		else
		{
			fwrite(rDevBuf, 1, numByWrSuccess, pFile);
		}

		numByToWr = size - numByWriteDone;
	}
	free(rDevBuf);
	fclose(pFile);

	cout << "Gen_Random_num_file : OUT" << endl;
}

void Gen_txt_to_bin_file(unsigned int Option)
{
	cout << "Gen_txt_to_bin_file : IN" << endl;

	FILE* txtFile = NULL;
	FILE* binFile = NULL;
	char strLine[1000];
	errno_t err;
	unsigned int line_count = 0;
	long long int Line_Val = 0;
	unsigned int tmp = 0;
	unsigned char* rDevBuf = NULL;

	if (Option == 1)
	{
		rDevBuf = (unsigned char*)malloc(4);
		err = fopen_s(&txtFile, "container_info.txt", "r");
		err = fopen_s(&binFile, "container_info.bin", "wb");
		cout << " container_info : txt to bin " << endl;
	}
	else if (Option == 2)
	{
		rDevBuf = (unsigned char*)malloc(4);
		err = fopen_s(&txtFile, "packet_info.txt", "r");
		err = fopen_s(&binFile, "packet_info.bin", "wb");
		cout << " packet_info : txt to bin " << endl;
	}
	else if (Option == 3)
	{
		rDevBuf = (unsigned char*)malloc(6);
		err = fopen_s(&txtFile, "raw_data.txt", "r");
		err = fopen_s(&binFile, "raw_data.bin", "wb");
		cout << " raw_data : txt to bin " << endl;
	}

	if ((txtFile != NULL) || (binFile != NULL))
	{
		while (1)
		{
			if (feof(txtFile)) break;
			strLine[0] = '\0';

			err = fscanf_s(txtFile, "%[^\n]\n", strLine, sizeof(strLine));
			if (err != 1) break;
			line_count++;
			sscanf_s(strLine, "%llx", &Line_Val);
			//	cout << line_count << " : "<< strLine << " : " << Line_Val << endl;
			if (Option == 3)
			{
				rDevBuf[0] = (unsigned char)((Line_Val >> 40) & 0xFF);
				rDevBuf[1] = (unsigned char)((Line_Val >> 32) & 0xFF);
				rDevBuf[2] = (unsigned char)((Line_Val >> 24) & 0xFF);
				rDevBuf[3] = (unsigned char)((Line_Val >> 16) & 0xFF);
				rDevBuf[4] = (unsigned char)((Line_Val >> 8) & 0xFF);
				rDevBuf[5] = (unsigned char)((Line_Val >> 0) & 0xFF);
				fwrite(rDevBuf, 1, 6, binFile);
			}
			else
			{
				rDevBuf[0] = (unsigned char)((Line_Val >> 24) & 0xFF);
				rDevBuf[1] = (unsigned char)((Line_Val >> 16) & 0xFF);
				rDevBuf[2] = (unsigned char)((Line_Val >> 8) & 0xFF);
				rDevBuf[3] = (unsigned char)((Line_Val >> 0) & 0xFF);
				fwrite(rDevBuf, 1, 4, binFile);
			}

		}
		free(rDevBuf);
		fclose(binFile);
		fclose(txtFile);
	}
	else
	{
		cout << " txt file not found" << endl;
	}

	cout << "Gen_txt_to_bin_file : OUT" << endl;
}

void Gen_bin_to_hex_file(void)
{
	cout << "Gen_bin_to_hex_file : IN" << endl;

	FILE* hexFile = NULL;
	FILE* binFile = NULL;
	errno_t err;
	unsigned char RdBuf[32];
	unsigned char WrBuf[76];
	unsigned int sz = 0;
	unsigned int i = 0, j = 0;
	unsigned int line_count = 0, line_count_tmp = 0;
	unsigned int checksum = 0;

	err = fopen_s(&binFile, "PCIe_SW.bin", "rb");
	err = fopen_s(&hexFile, "PCIe_SW.hex", "wb");


	if ((hexFile != NULL) || (binFile != NULL))
	{
		while (1)
		{
			fseek(binFile, 0L, SEEK_END);
			sz = ftell(binFile);
			fseek(binFile, 0L, SEEK_SET);

			for (j = 0; j < sz / 32; j++)
			{
				cout << "line_count : " << line_count << endl;
				checksum = 0;
				err = fread(RdBuf, 32, 1, binFile);
				WrBuf[0] = 0x3A;
				WrBuf[1] = 0x32;
				WrBuf[2] = 0x30;
				line_count_tmp = line_count * 32;
				WrBuf[3] = IntToHex(line_count_tmp >> 12);
				WrBuf[4] = IntToHex(line_count_tmp >> 8);
				WrBuf[5] = IntToHex(line_count_tmp >> 4);
				WrBuf[6] = IntToHex(line_count_tmp >> 0);
				WrBuf[7] = 0x30;
				WrBuf[8] = 0x30;
				for (i = 0; i < 32; i++)
				{
					WrBuf[i * 2 + 9] = IntToHex(RdBuf[i] >> 4);
					WrBuf[i * 2 + 10] = IntToHex(RdBuf[i]);
				}
				for (i = 1; i <= 36; i++)
				{
					checksum += ((((hexToint(WrBuf[i * 2 - 1]) << 4) & 0xF0) | ((hexToint(WrBuf[i * 2]) << 0) & 0xF)) & 0xFF);
				}
				checksum = ((~(checksum & 0xFF)) + 1);
				WrBuf[73] = IntToHex(checksum >> 4);
				WrBuf[74] = IntToHex(checksum);
				fwrite(WrBuf, 1, 75, hexFile);
				fwrite("\n", sizeof(char), 1, hexFile);
				line_count++;
			}
			if (sz % 32 != 0)
			{
				cout << "line_count : " << line_count << endl;
				checksum = 0;
				err = fread(RdBuf, sz % 32, 1, binFile);
				memset(&RdBuf[(sz % 32)], 0xFF, 32 - (sz % 32));
				WrBuf[0] = 0x3A;
				WrBuf[1] = 0x32;
				WrBuf[2] = 0x30;
				line_count_tmp = line_count * 32;
				WrBuf[3] = IntToHex(line_count_tmp >> 12);
				WrBuf[4] = IntToHex(line_count_tmp >> 8);
				WrBuf[5] = IntToHex(line_count_tmp >> 4);
				WrBuf[6] = IntToHex(line_count_tmp >> 0);
				WrBuf[7] = 0x30;
				WrBuf[8] = 0x30;
				for (i = 0; i < 32; i++)
				{
					WrBuf[i * 2 + 9] = IntToHex(RdBuf[i] >> 4);
					WrBuf[i * 2 + 10] = IntToHex(RdBuf[i]);
				}
				for (i = 1; i <= 36; i++)
				{
					checksum += ((((hexToint(WrBuf[i * 2 - 1]) << 4) & 0xF0) | ((hexToint(WrBuf[i * 2]) << 0) & 0xF)) & 0xFF);
				}
				checksum = ((~(checksum & 0xFF)) + 1);
				WrBuf[73] = IntToHex(checksum >> 4);
				WrBuf[74] = IntToHex(checksum);
				fwrite(WrBuf, 1, 75, hexFile);
				fwrite("\n", sizeof(char), 1, hexFile);
				line_count++;
			}
			for (j = line_count; j < 2048; j++)
			{
				cout << "line_count : " << line_count << endl;
				checksum = 0;
				memset(&RdBuf, 0xFF, 32);
				WrBuf[0] = 0x3A;
				WrBuf[1] = 0x32;
				WrBuf[2] = 0x30;
				line_count_tmp = line_count * 32;
				WrBuf[3] = IntToHex(line_count_tmp >> 12);
				WrBuf[4] = IntToHex(line_count_tmp >> 8);
				WrBuf[5] = IntToHex(line_count_tmp >> 4);
				WrBuf[6] = IntToHex(line_count_tmp >> 0);
				WrBuf[7] = 0x30;
				WrBuf[8] = 0x30;
				for (i = 0; i < 32; i++)
				{
					WrBuf[i * 2 + 9] = IntToHex(RdBuf[i] >> 4);
					WrBuf[i * 2 + 10] = IntToHex(RdBuf[i]);
				}
				for (i = 1; i <= 36; i++)
				{
					checksum += ((((hexToint(WrBuf[i * 2 - 1]) << 4) & 0xF0) | ((hexToint(WrBuf[i * 2]) << 0) & 0xF)) & 0xFF);
				}
				checksum = ((~(checksum & 0xFF)) + 1);
				WrBuf[73] = IntToHex(checksum >> 4);
				WrBuf[74] = IntToHex(checksum);
				fwrite(WrBuf, 1, 75, hexFile);
				fwrite("\n", sizeof(char), 1, hexFile);
				line_count++;
			}

			WrBuf[0] = 0x3A;
			WrBuf[1] = 0x30;
			WrBuf[2] = 0x30;
			WrBuf[3] = 0x30;
			WrBuf[4] = 0x30;
			WrBuf[5] = 0x30;
			WrBuf[6] = 0x30;
			WrBuf[7] = 0x30;
			WrBuf[8] = 0x31;
			WrBuf[9] = IntToHex(0xF);
			WrBuf[10] = IntToHex(0xF);
			fwrite(WrBuf, 1, 11, hexFile);
			fwrite("\n", sizeof(char), 1, hexFile);
			break;
		}
		fclose(binFile);
		fclose(hexFile);
	}
	else
	{
		cout << " bin file not found" << endl;
	}

	cout << "Gen_bin_to_hex_file : OUT" << endl;
}


void Gen_bin_to_cfg_file(void)
{
	cout << "Gen_bin_to_cfg_file : IN" << endl;

	FILE* cfgFile = NULL;
	FILE* binFile = NULL;
	errno_t err;
	unsigned char RdBuf[32];
	unsigned int sz = 0;
	unsigned int i = 0, j = 0;
	unsigned int line_count = 0, line_count_tmp = 0;
	unsigned int checksum = 0;
	unsigned int Addr = 0, Val = 0;

	err = fopen_s(&binFile, "PCIe_SW.bin", "rb");
	err = fopen_s(&cfgFile, "PCIe_SW.cfg", "wb");


	if ((cfgFile != NULL) || (binFile != NULL))
	{
		fseek(binFile, 0L, SEEK_END);
		sz = ftell(binFile);
		fseek(binFile, 0L, SEEK_SET);
		fprintf_s(cfgFile, "PES24NT6AG2 - PCI Express Switch(6 ports) - x4 Transparent\n");
		for (j = 0; j < sz / 7; j++)
		{
			Addr = 0;
			Val = 0;
			checksum = 0;
			err = fread(RdBuf, 7, 1, binFile);
			Addr = (RdBuf[2] << 8);
			Addr |= (RdBuf[1] << 0);
			Addr = Addr * 4;

			Val = (RdBuf[6] << 24);
			Val |= (RdBuf[5] << 16);
			Val |= (RdBuf[4] << 8);
			Val |= (RdBuf[3] << 0);

			cout << "Addr : " << std::hex << Addr << " Val : " << std::hex << Val << endl;

			fprintf_s(cfgFile, "0x%08X 0x%08X\n", Addr, Val);
		}

		fclose(binFile);
		fclose(cfgFile);
	}
	else
	{
		cout << " bin file not found" << endl;
	}
	cout << "Gen_bin_to_cfg_file : OUT" << endl;
}

void Gen_RAM_XML_file(unsigned int Option)
{
	FILE* fd, * nfd;
	char str[50], * ptr;
	int count = 0;
	char addr1[5], addr2[5], val[5];

	if (Option == 1)
	{
		fopen_s(&fd, "avpsm_ceh_pll1_reg_file.txt", "r");
	}
	else if (Option == 2)
	{
		fopen_s(&fd, "avpsm_ceh_pll2_reg_file.txt", "r");
	}
	else
	{
		fd = NULL;
		printf("Invalid PLL %d Selected !!!\n", Option);
	}
	if (fd == NULL) {
		printf("Source File open failure !!!\n");
	}

	if (Option == 1)
	{
		fopen_s(&nfd, "PLL1_XML_Script.txt", "w+");
	}
	else if (Option == 2)
	{
		fopen_s(&nfd, "PLL2_XML_Script.txt", "w+");
	}
	else
	{
		nfd = NULL;
		printf("Invalid PLL %d Selected !!!\n", Option);
	}
	
	if (nfd == NULL) {
		printf("Dest File open failure !!!\n");
	}

#if !XML_FILE
	/* for U-boot script */
	fprintf(nfd, "pll2program2=echo PLL Script file creation !!!;");
	fprintf(nfd, " %s;", CMD1);
	fprintf(nfd, " %s;", CMD2);
#endif
	if ((nfd != NULL) && (fd != NULL))
	{
		fprintf(nfd, "<adapter>\n");
		fprintf(nfd, "<configure i2c=%c%d%c spi=%c%d%c gpio=%c%d%c tpower=%c%d%c pullups=%c%d%c/>\n", '"', 1, '"', '"', 1, '"', '"', 0, '"', '"', 1, '"', '"', 1, '"');
		fprintf(nfd, "<i2c_bitrate khz=%c%d%c/>\n", '"', 400, '"');
		while (fgets(str, 50, fd))
		{
			if (strstr(str, "0x"))
			{
				count++;
				ptr = str;
				ptr = ptr + 2;
				strncpy_s(addr1, ptr, 2);
				ptr = ptr - 2;
				addr1[2] = '\0';
				ptr = ptr + 4;
				strncpy_s(addr2, ptr, 2);
				addr2[2] = '\0';
				ptr = ptr + 5;
				strncpy_s(val, ptr, 2);
				val[2] = '\0';
#if XML_FILE
				printf("addr1 = %s, addr2 = 0x%s, val = %s\n", addr1, addr2, val);
				// XML script creation
				fprintf(nfd, "<i2c_write addr=\"0x6f\" count=\"2\" radix=\"16\">20 %s</i2c_write>\n", addr1);
				fprintf(nfd, "<i2c_write addr=\"0x6f\" count=\"2\" radix=\"16\">21 %s</i2c_write>\n", addr2);
				fprintf(nfd, "<i2c_write addr=\"0x6f\" count=\"2\" radix=\"16\">22 %s</i2c_write>\n", val);
				fprintf(nfd, "<i2c_write addr=\"0x6f\" count=\"2\" radix=\"16\">2A 01</i2c_write>\n");
				if (count == 4)
				{
					fprintf(nfd, "<sleep ms=%c%d%c/>\n", '"', 300, '"');
				}
#else
				/* for u-boot script */
				fprintf(nfd, " i2c mw 0x6F 0x20 0x%s 1;", addr1);
				fprintf(nfd, " i2c mw 0x6F 0x21 0x%s 1;", addr2);
				fprintf(nfd, " i2c mw 0x6F 0x22 0x%s 1;", val);
				fprintf(nfd, " i2c mw 0x6F 0x2A 0x01 1;");
				if (count == 4)
					fprintf(nfd, " sleep 1;");
#endif
			}
		}
		fprintf(nfd, "</adapter>\n");
		fclose(fd);
		fclose(nfd);
	}
}

unsigned char record[133];

void Gen_ROM_XML_file(unsigned int Option)
{
	unsigned char* str;
	FILE* fd_bin, * fd_xml;
	unsigned int size, ret, loc = 0, num_records = 0, i;
	unsigned int rec_size;
	/* size maitains total size of file*/
	/* loc is location in the str array */
	/* num_records is total records found*/
	/* rec_size maintains the size of record */


	if (Option == 1)
	{
		fopen_s(&fd_bin, "avpsm_ceh_pll1_reg_file.bin", "r");
	}
	else if (Option == 2)
	{
		fopen_s(&fd_bin, "avpsm_ceh_pll2_reg_file.bin", "r");
	}
	else
	{
		fd_bin = NULL;
		printf("Invalid PLL %d Selected !!!\n", Option);
	}
	if (fd_bin == NULL) {
		printf("Source File open failure !!!\n");
	}

	if (Option == 1)
	{
		fopen_s(&fd_xml, "PLL1_XML_Script.xml", "w+");
	}
	else if (Option == 2)
	{
		fopen_s(&fd_xml, "PLL2_XML_Script.xml", "w+");
	}
	else
	{
		fd_xml = NULL;
		printf("Invalid PLL %d Selected !!!\n", Option);
	}

	if (fd_xml == NULL) {
		printf("Dest File open failure !!!\n");
	}

	if ((fd_bin != NULL) && (fd_xml != NULL))
	{

		fseek(fd_bin, 0, SEEK_END);
		size = ftell(fd_bin);
		fseek(fd_bin, 0, SEEK_SET);

		str = (unsigned char*)malloc((sizeof(char) * size) + 1);
		ret = fread(str, 1, size, fd_bin);

		while (*str == 0x24) {
			rec_size = *(str + 1) + 2;
			printf("Found Record %d with size = %d\n", num_records + 1, rec_size);
			memcpy(record, str, rec_size);

			/**********dumping to xml************/
			fprintf(fd_xml, "<i2c_write addr=\"0x6f\" count=\"%d\" radix=\"16\">", rec_size);
			for (i = 0; i < rec_size; i++)
				fprintf(fd_xml, "%x ", record[i]);

			fseek(fd_xml, -1, SEEK_CUR);

			fprintf(fd_xml, "</i2c_write>\n");
			if (num_records < 487)
				fprintf(fd_xml, "<sleep ms=\"100\"/>\n");
			else
				fprintf(fd_xml, "<sleep ms=\"7000\"/>\n");

			fprintf(fd_xml, "<i2c_write addr=\"0x6f\" count=\"1\" radix=\"16\">FE</i2c_write>\n");
			fprintf(fd_xml, "<i2c_read addr=\"0x6f\" count=\"1\"/>\n");
			num_records++;
			str = str + rec_size;
		}
		free(str);
		fclose(fd_xml);
		fclose(fd_bin);
	}
}
