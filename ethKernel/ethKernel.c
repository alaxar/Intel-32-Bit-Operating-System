int main() {
    unsigned char *VGA = (unsigned char *)0xB8000;
    VGA[0] = 'A';
    VGA[1] = 0x0f;
    VGA[2] = 'B';
    // while(1);
}