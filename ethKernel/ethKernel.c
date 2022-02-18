
int main() {
    unsigned char *pixel = (unsigned char*)0xE0000000;
    pixel[384*768+512] = 0xffffffff;
    // while(1);
}