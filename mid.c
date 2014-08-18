#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define SIZE_Q 4
//#define PQ_NUM (99 / SIZE_Q)

//#define SIZE_Q 5000
#define SIZE_Q 400
//#define SIZE_Q 100
#define PQ_NUM (100000 / SIZE_Q)

typedef long long LL;

typedef struct {
  int fds[2];
  int cnt;
} PipeQ;

//LL arr[SIZE_Q];
LL* arr;
//LL arr[5000];
PipeQ* pq;

void initPQ(PipeQ* q) {
  q->cnt = 0;
  pipe(q->fds);
}

LL popPQ(PipeQ* q) {
  if (q->cnt <= 0) {
    q->cnt = -1;
    return LLONG_MAX;
  }
  q->cnt--;
  LL r;
  read(q->fds[0], &r, sizeof(r));
  return r;
}

int cmp(const void* xp, const void* yp) {
  LL x = *(LL*)xp;
  LL y = *(LL*)yp;
  if (x > y)
    return 1;
  if (x < y)
    return -1;
  return 0;
}

void flushPQ(PipeQ* q, int sz) {
#if 1
  int i;
  qsort(arr, sz, 8, cmp);
  for (i = 0; i < sz; i++) {
    //printf("%lld\n", arr[i]);
    write(q->fds[1], &arr[i], sizeof(LL));
  }
  q->cnt = sz;
#else
  q->cnt = 0;
#endif
}

int main() {
  int i, j, qi, pqi, qnum = 0;
  arr = malloc(SIZE_Q * sizeof(LL));
  pq = malloc(PQ_NUM * sizeof(PipeQ));

  memset(arr, 0, sizeof(arr));

  for (i = 0; i < PQ_NUM; i++) {
    initPQ(&pq[i]);
  }

  int n;
  scanf("%d",&n);

  //sleep(1);

  int tot = 0;
  for(i = 0; i < n + 1; i++){
    j = i % SIZE_Q;

    pqi = (i - 1) / SIZE_Q;
    qi = i / SIZE_Q;
    if (i && (i == n || pqi != qi)) {
      int sz = SIZE_Q;
      if (i == n && j)
        sz = j;
      qnum++;
      /* printf("come pqi=%d i=%d sz=%d arr[0]=%lld arr[-1]=%lld\n", */
      /*        pqi, i, sz, arr[0], arr[SIZE_Q-1]); */
      flushPQ(&pq[pqi], sz);
      /* printf("come i=%d sz=%d arr[0]=%lld arr[-1]=%lld\n", */
      /*        i, sz, arr[0], arr[sz-1]); */
      tot += sz;
    }

    if (i != n) {
      scanf("%lld", &arr[j]);
    }
  }

  //sleep(1);
  //printf("%lld\n", 1); return 0;

  //fprintf(stderr, "qnum=%d tot=%d\n", qnum, tot);
  //sleep(1);

  for (i = 0; i < qnum; i++) {
    arr[i] = popPQ(&pq[i]);
  }

  LL min_val;
  for (i = 0; i < n / 2 + 1; i++) {
    min_val = LLONG_MAX;
    int min_qi = -1;
    for (qi = 0; qi < qnum; qi++) {
      //if (arr[qi] != -1 && min_val >= arr[qi]) {
      //if (/*arr[qi] != -1 &&*/ min_val >= arr[qi]) {
      if (pq[qi].cnt >= 0 && min_val >= arr[qi]) {
        min_val = arr[qi];
        min_qi = qi;
      }
    }

    //if (min_qi == -1)
    //  abort();

#if 0
    printf("%lld %d (%lld vs %lld vs %lld vs %lld vs %lld vs %lld)\n",
           min_val, min_qi,
           arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
#endif
    arr[min_qi] = popPQ(&pq[min_qi]);
#if 0
    printf("%lld %d (%lld vs %lld vs %lld vs %lld vs %lld vs %lld)\n",
           min_val, min_qi,
           arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
#endif
  }

  //if (min_val > 700000)
  //  sleep(1);

#if 0
  if (min_val < 0)
    sleep(2);
  else if (min_val > 0)
    sleep(1);
#endif

  printf("%lld", min_val);

  //sleep(1);
  return 0;
}
