/* Scott Little */

/*
    f(i,j) = { f(i) = 0
             { max(f[i], f[i-V[j]]+1) if V[i] <= j

    T(n) = O(n*D)
*/
static int knapsack(const int D, const int n, std::vector<int> V) {
   int f[D + 1];
   f[0] = 0;

   for (int i = 1; i <= D; i++) { f[i] = INT_MAX - 1; }

   for (int i = 0; i < V.size(); i++) {
      for (int j = 1; j <= D; j++) {
         if (V[i] <= j) { f[j] = std::min(f[j - V[i]] + 1, f[j]); }
      }
   }
   return f[D];
}

/*
    c[i,j] = { c[i-1, j-1]+1 if x[i] == y[j]
             { max(c[i,j-1], c[i-1, j) otherwise

    T(n) = O(n + m + nm + (m || n)) = O(nm)
*/
static std::vector<int> LCS(std::vector<int>& A, std::vector<int>& B) {
   int              n = A.size(), m = B.size();
   int              i = 0, j = 0;
   std::vector<int> ret;
   int              LCS[n + 1][m + 1];

   for (i = 0; i <= n; i++) LCS[i][0] = 0;
   for (j = 0; j <= m; j++) LCS[0][j] = 0;

   for (i = 1; i <= n; i++) {
      for (j = 1; j <= m; j++) {
         if (A[i - 1] == B[j - 1])
            LCS[i][j] = LCS[i - 1][j - 1] + 1;
         else
            LCS[i][j] = std::max(LCS[i][j - 1], LCS[i - 1][j]);
      }
   }

   i = n, j = m;

   while (i && j) {
      if (A[i - 1] == B[j - 1]) {
         ret.push_back(A[i - 1]);
         i--, j--;
      } else {
         if (LCS[i][j - 1] > LCS[i - 1][j])
            j--;
         else
            i--;
      }
   }

   return ret;
}

/*
    Base case: A[i]     if i = 0
    A[i] = max(A[i-1] + A[i], A[i]) otherwise

    T(n) = O(n)
*/

int MaxSubarray(std::vector<int>& A) {
   int max_so_far = 0, max_ending_here = 0;

   for (int i = 0; i < A.size(); i++) {
      max_ending_here = max_ending_here + A[i];
      max_ending_here = std::max(max_ending_here, 0);
      max_so_far      = std::max(max_so_far, max_ending_here);
   }

   return max_so_far;
}