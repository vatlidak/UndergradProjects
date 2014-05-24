#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "CompDecomp.h"

int main(int argc, char* argv[])
{
	FILE* f_in, *f_out;
	int maxbits;
	int i, temp;
	int flag,flag1,flag2,flag3;

////////////////////////////////////////////////////////////////////
	flag = 0;							/*������� ��� �� �� ������� � ������� -b ��� ��������� �� maxbits*/
	for(	i=0; i< argc; i++ )
	{
		if ( (temp = strcmp(argv[i],"-b")) == 0 )
		{	
			maxbits = atoi( argv[i+1] );
			flag = 1;
			break;
		}
	}
	if ( flag != 1 )						/*�� �� ������� ������� default ���� �� 16*/
		maxbits = 16;
///////////////////////////////////////////////////////////////////
	flag1 = 0;
	for(	i=0; i< argc; i++ )					/*������� ��� �� �� ������� � ������� -i ��� ��������� �� ������ �������*/
	{
		if ( (temp = strcmp(argv[i],"-i")) == 0 )
		{
			f_in=fopen(argv[i+1],"rb");
			flag1 = 1;
			break;
		}
	}
	if ( flag1 != 1)
		f_in = stdin;
///////////////////////////////////////////////////////////////////
	flag2 = 0;
	for(	i=0; i< argc; i++ )					 /*������� ��� �� �� ������� � ������� -� ��� ��������� �� ������ ������*/
	{
		if ( (temp = strcmp(argv[i],"-o")) == 0 )
		{
			f_out=fopen(argv[i+1],"wb");
			flag2 = 1;
			break;
		}
	}
	if ( flag2 != 1)
		f_out = stdout;
/////////////////////////////////////////////////////////////////////
	flag3 = 0;
	for(	i=0; i< argc; i++ )					/*������� ��� �� �� ������� � ������� -d ��� ��������� �� �� ����� ��������
									  � �����������*/
	{
		if ( (temp = strcmp(argv[i],"-d")) == 0 )
		{
			decompression(f_in,f_out);
			flag3 = 1;
			break;
		}
	}
	if ( flag3 != 1 )
		compression(f_in,f_out,maxbits);
////////////////////////////////////////////////////////////////////////	
	for(	i=0; i< argc; i++ )					/*������� ��� �� �� ������� � ������� -p ��� ��������� ��� �� ���������
									  �� ������� ���������*/
	{
		if ( (temp = strcmp(argv[i],"-p")) == 0 )
		{
			fprintf(stderr,"%.2f %% compression achieved\n",per);
			break;
		}
	}
	if ( flag1 ==1 || flag3==1 )					/*�������� ������� ������� ��� ������,�� ����� �������*/
		fclose(f_in);
	if ( flag2==1 )
		fclose(f_out);
	return 1;
}	
