/* Common Bit Tasks: Getting and Setting */

bool getKthBit(int num, int k) {
  return ((num & (1 << k)) != 0);
}

int setKthBit(int num, int k) {
  return num | (1 << k);
}

int clearKthBit(int num, int k) {
  int mask = ~(1 << k);
  return num & mask;
}

int clearBitsMSBthroughK(int num, int k) {
  int mask = (1 << k) - 1;
  return num & mask;
}

int clearBitsKthrough0(int num, int k) {
  int mask = (-1 << (k+1));
  return num & mask;
}

int updateKthBit(int num, int k, bool isBit1) {
  int value = isBit1 ? 1 : 0;
  int mask = ~(1 << k);
  return (num & mask) | (value << k);
}
