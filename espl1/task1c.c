
void charToBin(char c, char binRepr[], int (*bitGetter)(int), int (*shifter)(int));
int shiftLeft(int i);
int getMSB(int i);

void charToBinFromMSB(char c, char binRepr[]) {
    charToBin(c, binRepr, getMSB, shiftLeft);
}