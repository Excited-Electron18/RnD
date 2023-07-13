#pragma once
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MAX_PKT_SIZE 0xFFFF
#define XML_FILE 1

void Gen_Incr_num_file(unsigned int size, char *FilePath);
void Gen_Random_num_file(unsigned int size, char *FilePath);
void Gen_txt_to_bin_file(unsigned int Option);
void Gen_bin_to_hex_file(void);
void Gen_bin_to_cfg_file(void);
void Gen_RAM_XML_file(unsigned int Option);
void Gen_ROM_XML_file(unsigned int Option);
#endif