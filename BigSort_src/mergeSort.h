#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include "settings.h"

/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Status;

/* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
typedef int Boolean;

/* k+1���ļ�ָ��(fp[k]Ϊ���ļ�ָ��)��ȫ�ֱ��� */
FILE *fp[k + 1];

/* ����������ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ */
int input(int i, data_type *a);
void output(int i);
void Adjust(data_type *ls, data_type s);
void CreateLoserTree(data_type *ls);
void K_Merge(data_type *ls, data_type *b);
int mergeSort();




