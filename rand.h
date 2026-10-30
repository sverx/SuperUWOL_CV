static unsigned long int next = 1;

unsigned char rand (void) {
    next = next * 1103515245UL + 12345;
    return (unsigned char) (next / 65536) & 255;
}

void srand (unsigned int seed) {
    next = seed;
}

// Change this for something FASTER!
