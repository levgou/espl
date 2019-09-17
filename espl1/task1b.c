
void charToBin(char c, char binRepr[], int (*bitGetter)(int), int (*shifter)(int));
int shiftRight(int i);
int getLSB(int i);

void charToBinFromLSB(char c, char binRepr[]) {
    charToBin(c, binRepr, getLSB, shiftRight);
}