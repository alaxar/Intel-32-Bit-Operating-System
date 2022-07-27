#include "pci.h"
#include "../../include/types.h"

uint32_t read_pci_config(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    uint32_t v;
    long config_address = (0x80000000 | (slot << 11) | (function << 8) | offset); 
    port_dword_out(0xCF8, config_address);
    v = port_dword_in(0xCFC);
    return v;
}

void enumerate_buses() {
    uint32_t device_id;
    uint8_t class, subclass;
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < 32; j++) {
            if(read_pci_config(i, j, 0, 0) != 0xFFFF) {
                device_id = read_pci_config(i, j, 0, 0);
                // printf(itoa(device_id), -1, -1, -1);
                if(device_id == 269385862) {
                    class = read_pci_config(i, j, 0, 8);
                    subclass = read_pci_config(i, j, 0, 7);
                    printf(itoa(class),  -1,  -1, -1);
                    print_char('\n', -1, -1, -1);
                    printf(itoa(subclass),  -1,  -1, -1);
                    print_char('\n', -1, -1, -1);
                }
            }
        }
    }
}