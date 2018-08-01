#include <stdio.h>
#include <stdint.h>

uint8_t EEPROM_read(uint16_t address)
{
	FILE *eeprom_file;
	eeprom_file = fopen("eeprom.bin", "r");
	fseek(eeprom_file, address, 0);
	uint8_t buffer;
	fread(&buffer, 1, 1, eeprom_file);
	return buffer;
	fclose(eeprom_file);
}
void EEPROM_write(uint16_t address, uint8_t value)
{
	FILE *eeprom_file;
	eeprom_file = fopen("eeprom.bin", "r+");
	fseek(eeprom_file, address, 0);
	uint8_t buffer[1] = {value};
	fwrite(&buffer, 1, 1, eeprom_file);
	fclose(eeprom_file);
}

int main(int argc, char const *argv[])
{
	EEPROM_write(5, 'G');
	//printf("%c\n", EEPROM_read(5));
	return 0;
}