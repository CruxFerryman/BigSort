#define _CRT_SECURE_NO_WARNINGS

#include "mergeSort.h"

/* ȫ�ֱ��� */
data_type *b;
data_type *ls;

/* �ӵ�i���ļ�(��i���鲢��)����öε�ǰ��1����¼�Ĺؼ��ֵ����� */
int input(int i, data_type *a) 
{
	int j = fread(a, sizeof(data_type), 1, fp[i]);
	if (j > 0) {
//		printf("%d\n", *a);
		return 1;
	}
	else {
		return 0;
	}
}

/* ����i���ļ�(��i���鲢��)�е�ǰ�ļ�¼д������鲢�� */
void output(int i) 
{
	fwrite(&b[i], sizeof(data_type), 1, fp[k]);
}

/* �ش�Ҷ�ӽ��b[s]�������ls[0]��·��������������*/
void Adjust(data_type *ls, data_type s)
{
	int t;
	data_type i;

	/* ls[t]��b[s]��˫�׽�� */
	t = (s + k) / 2;
	while (t > 0) {
		/* sָʾ�µ�ʤ�� */
		if (b[s] > b[ls[t]]) {
			i = s;
			s = ls[t];
			ls[t] = i;
		}
		t = t / 2;
	}
	ls[0] = s;
}

/**
* ��֪b[0]��b[k-1]Ϊ��ȫ������ls��Ҷ�ӽ�㣬����k���ؼ��֣��ش�Ҷ��
* ������k��·����ls������Ϊ��������
*/
void CreateLoserTree(data_type *ls)
{
	int i;
	b[k] = MINKEY;

	/* ����ls�С����ߡ��ĳ�ֵ */
	for (i = 0; i < k; ++i) {
		ls[i] = k;
	}

	/* ���δ�b[k-1]��b[k-2]������b[0]������������ */
	for (i = k - 1; i >= 0; --i) {
		Adjust(ls, i);
	}
}

/**
* ���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢�Ρ�
* b[0]��b[k-1]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ���k������鲢���е�ǰ��¼�Ĺؼ��֡�
*/
void K_Merge(data_type *ls, data_type *b)
{
	int i;
	data_type q;

	/* �ֱ��k������鲢�ζ��˸öε�ǰ��һ����¼�Ĺؼ��ֵ����� */
	for (i = 0; i < k; ++i) {
		input(i, &b[i]);
	}

	/* ��������ls��ѡ����С�ؼ���Ϊb[ls[0]].key */
	CreateLoserTree(ls);

	while (b[ls[0]] != MAXKEY) {
		/* qָʾ��ǰ��С�ؼ������ڹ鲢�� */
		q = ls[0];

		/* �����Ϊq�Ĺ鲢���е�ǰ���ؼ���Ϊb[q].key���ļ�¼д������鲢�� */
		output(q);

		/* �ӱ��Ϊq������鲢���ж�����һ����¼�Ĺؼ��� */
		if (input(q, &b[q]) > 0) {
			/* ������������ѡ���µ���С�ؼ��� */
			Adjust(ls, q);
		}
//		fflush(fp[k]);
	}

	/* �������ؼ���MAXKEY�ļ�¼д������鲢�� */
	output(ls[0]);
	fflush(fp[k]);
}

int mergeSort() 
{
	b = (data_type*)malloc((k + 1)*sizeof(data_type));
	int i = 0;
	char fname[32] = "";
	char fout[32] = "result.bin";
	ls = (data_type*)malloc(k*sizeof(data_type));;

	/* ���δ����ļ� */
	#pragma omp parallel private(i, fname) num_threads(8)
	{	
		#pragma omp for
		for (i = 0; i < k; i++) {
			/* �Զ��ķ�ʽ�����ļ�*/
			sprintf(fname, "%s%d%s", "temp", i + 1, ".bin");
			fp[i] = fopen(fname, "rb");
		}
	}
	/* ��д�ķ�ʽ�򿪴��ļ�fout */
	fp[k] = fopen(fout, "wb");

	/* ���ð�����ls��k������鲢���еļ�¼�鲢������鲢�Σ������ļ�fout */
	K_Merge(ls, b);

	/* �ر��ļ�f0,f1,�����ļ�fout */
	for (i = 0; i <= k; i++) {
		fclose(fp[i]);
	}
	/* �رմ��ļ�fout */
	fclose(fp[k]);
	free(b);
	printf("Merge Sort Success!");
	return 1;
}