#define max(a,b) ((a) > (b) ? (a) : (b))

int flipBit(int a) {
  if (~a == 0)
    return 4 * 8; // 4 bytes are allocated for integer data type and 1 byte equals 8 bits

  int currLen = 0;
  int prevLen = 0;
  int maxLen = 1;
  while (a != 0) {
    if ((a & 1) == 1) {
      currLen++;
    } else if ((a & 1) == 0) {
      prevLen = (a & 2) == 0 ? 0 : currLen;
      currLen = 0;
    }
    maxLen = max(maxLen, prevLen + currLen + 1);
    a /= 2; // this bitwise operation is equal to 'a >>>= 1;' in Java
  }

  return maxLen;
}
