int getNext(int n) {
  int c = n;
  int c0 = 0;
  int c1 = 0;

  while (((c & 1) == 0) && (c != 0)) {
    c0++;
    c >>= 1;
  }
  while ((c & 1) == 1) {
    c1++;
    c >>= 1;
  }

  if (c0 + c1 == 31 || c0 + c1 == 0)
    return -1;

  int p = c0 + c1;

  n |= (1 << p);
  n &= ~((1 << p) - 1);
  n |= (1 << (c1 - 1)) - 1;

  return n;
}

int getPrev(int n) {
  int tmp = n;
  int c0 = 0;
  int c1 = 0;
  while (tmp & 1 == 1) {
    c1++;
    tmp >>= 1;
  }

  if (tmp == 0)
    return -1;

  while (((tmp & 1) == 0) && (tmp != 0)) {
    c0++;
    tmp >>= 1;
  }

  int p = c0 + c1;
  n &= ((~0) << (p+1));
  int mask = (1 << (c1 + 1)) - 1;
  n |= mask << (c0 - 1);

  return n;
}
