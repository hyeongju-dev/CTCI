// CAUTION: In C++, there's no sign-preserving and unsigned right shift. We have only the >> operator, whose behavior on negative signed values is implementation-defined.
int swapOddEvenBits(unsigned int x) {
  return (((x & 0xaaaaaaaaa) >>> 1) | ((x & 0x55555555) << 1));
}
