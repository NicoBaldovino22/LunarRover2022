float Smooth(int prev, int next) {
  return ((next * (Agressivness)) + (prev * (1 - Agressivness)));
}
