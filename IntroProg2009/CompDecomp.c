#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bit_io.h"
#include "CompDecomp.h"
#include "dict.h"
#define MAXLEN 1000

int compression(FILE* f_in, FILE* f_out,int maxbits)		/*��������� ���������*/
{								/*�������� �� ������� ������� ��� ������ �� ��������*/
	int i;
     	int nbits, BYTE, read_bytes, word_code;
	long int comp_bits;					
     	char Character; 
     	char STRING[MAXLEN];
     	bit_buf* b_buf;
	Treeptr Root;
	int code;
	
     	code=257;						/*� ������ ������� ���� ���� ASCHII ��� ��� ������ �����������*/
     	Root=NULL;						/*� ���� ��� �������� �������*/
     	nbits = 9;
     	if ( (b_buf=bit_init(f_out)) == NULL )			/*������� ���� ��� �� buffer �� ��� bit_init*/
     	{							/*���� �� �����*/
     		fprintf(stderr,"Out of Memory\n");
          	return -1;
     	}
	bit_write(maxbits-9,3,b_buf);					/* ����� ����� ��� ������ ��� maxbits */
     	i=0;
     	if ( (BYTE=fread(&STRING[i],sizeof(char),1,f_in)) != 1)		/*������� �� ����� ��������� ��� �� ����� �������*/
     	{
           	fprintf(stderr,"file is empty\n");			/*��� ������ �� ����� �����*/
           	return -1;
     	}
	i++;
     	read_bytes = 1;						/*������� ��� bytes ��� ����������� ��� ��� ���������� ��� ��������*/ 
	comp_bits=0;						/*������� ��� bytes ��� ������������ ��� ��� ���������� ��� ��������*/
	while ( feof(f_in) == 0 ) 				/*� feof ���������� 0 ���� ����� ��� ����� ��� �������� �������*/
	{
     		BYTE=fread(&Character,sizeof(char),1,f_in);	/*������� ��� ��������� ��� �� ����� �������*/
        	if ( BYTE != 1 )
     			break;
        	read_bytes+=BYTE;
          	STRING[i]=Character;				/*����� �� ��������� ��� string*/
		i++;
          	STRING[i]='\0';
          	if ( treesearch(Root, STRING) == 0 )		/* ��� � ��������� ��������� ��� string ��� ������� ��� ������*/
          	{						/* ����� ���� ����� ��� ����� ,����� �� ��� ���������*/
           		STRING[i-1]='\0';
			if ( strlen(STRING)== 1 )		/*�� ����� ����������, � ������� ����� � ASCHII*/
				bit_write(STRING[i-2],nbits,b_buf);
               		else					/*������ ������ �� ������ ��� �� ������*/
               		{
             			word_code = searchcode(Root, STRING);
              			bit_write(word_code,nbits,b_buf);
            		}
			comp_bits += nbits;
			if ( code == pow(2,nbits) )			/* �� �� ������ ����� ��� 2^nbits  */ 
			{					
				if (nbits != maxbits)			/* ���� ���������� ��'���� �����*/
					nbits++;
				if (8*read_bytes < comp_bits)		/* �� �� ������� �������� ��������*/
				{
					fprintf(stderr,"No compression\n");
					bit_write(256,nbits,b_buf);	/*����� �� ������ ����������� �� nbits*/
					deletetree(Root);		/*�������� �� ������*/
					nbits = 9;			/*���������� ����*/
					comp_bits = 0;
					Root = NULL;
					code=257;
				}
			}
			if ( code != pow(2,maxbits) )			/* ��� �� ������ ��� ���� �������*/
			{
				STRING[i-1]=Character;			/*�������� ��� ����� ��������� ���� �� �� ��� ���������*/
	          		STRING[i]='\0';				/*��� ������*/
				addtree(&Root,STRING,code);
				code++;
			}
	     		STRING[0]=Character;			
         		STRING[1]='\0';
           		i=1;
     		}
	}
	if ( strlen(STRING)== 1 )				/*����� ���� ����� �� ��������� ������*/
 		bit_write(STRING[i-2],nbits,b_buf);
	else
    	{
         	word_code = searchcode(Root, STRING);
     	bit_write(word_code,nbits,b_buf);
    	}
	comp_bits+=nbits;					/*��������� �� ������� ���������*/
	per = ((float)( read_bytes*8-comp_bits)/ ((float )read_bytes*8))*100;
	bit_flush(b_buf);					/*������� �� buffer ���� �����*/
	free(b_buf);
	return 0;
}

int decompression ( FILE *f_in, FILE *f_out )
{
	int i;
	int x;
	int nbits, maxbits, old_code, new_code, code;
	char Character;
	char STRING[MAXLEN];
	char *s;
	bit_buf* b_buf;
	transcode* trans_table;

	nbits = 9;
	code = 257;					/*� ������ ������� ���� ���� ASCHII ��� ��� ������ �����������*/
    	if ( (b_buf=bit_init(f_in)) == NULL )		/*������� ���� ��� �� buffer �� ��� bit_init*/
    	{						/*��� ���� �� �������*/
    		fprintf(stderr,"Out of Memory\n");
         	return -1;
    	}
	x = bit_read( 3, b_buf );			/*�� ���� ����� bits ��� ������ �� maxbits*/
	maxbits=x+9;

	trans_table = calloc ( pow(2,maxbits) , sizeof(transcode) );	/*������� ���� ��� ��� ������ ����������*/
	for ( i=0; i<=255; i++)						/*�� ������ 255 ������ ����� �� ASCHII �������*/
	{								/*��� ������������� �� ����������*/
		trans_table[i].code = i;
		if ( (trans_table[i].word=calloc(1,sizeof(char))) == NULL ){
			fprintf(stderr,"Malloc error\n");
			return -1;
		}
		trans_table[i].word[0]=i;
	}
	trans_table[256].code = 256;				/*� 256 ����� � ������� �����������*/
	for(i = 257; i<(int)pow(2,maxbits); i++)		/*� ��������� ������� ��������������� �� -1 ��� ������*/
		trans_table[i].code = -1;
 	old_code = bit_read( nbits, b_buf );			/*������� �� ����� ������*/
	sprintf(&Character,"%c",old_code);			/*��� ������ ��� char*/
	fprintf(f_out,"%c",Character);				/*��� ����� �� ��������� ��� ���� �����*/
	while ( (new_code = bit_read ( nbits, b_buf )) != (-2) )	/*������� ��������� ������ ��� ��� �����*/
	{
		STRING[0]='\0';
		if ( new_code == (-1) )				
			fprintf(stderr,"Reading error\n");
		if ( new_code == trans_table[new_code].code )   /* �� ������� ���� ������ ����������*/
		{						/*���� �� ��������� ��� ��� string*/
			strcpy ( STRING , trans_table[new_code].word );
		}
		else						/* �� ��� ������� ���� ��� string �� ��������� ��� */
		{						/*������ ������� ��� ����8��� �� char*/
			strcpy ( STRING , trans_table[old_code].word );
			STRING[strlen(STRING)] = Character;
			STRING[strlen(STRING)+1] = '\0';
		}
		fprintf(f_out,"%s",STRING);			/*����� ���� ����� �� ��������� ��� string*/
		Character=STRING[0];				/*���� ��� char �� ����� ��������� ��� string*/	
		if ( new_code == 256)				/*������ �� ��������� ��� �� ������ �����������*/
		{						/*�� ��� ���������� ���� �� ������ ���*/
			nbits = 9;
			code = 257;
			for(i = 257; i<(int)pow(2,maxbits); i++)
				trans_table[i].code = -1;
		}	
		if ( code == (int)pow(2,nbits)-1 && nbits<maxbits )	
			nbits++;
		if ( code != (int)pow(2,maxbits) )		/* �� � ������� ���� � ���� ��������*/
		{
			trans_table[code].code = code;		/*�������� �� ����� ������ ��� �� char ��� ������*/
			s= trans_table[old_code].word;
			trans_table[code].word = calloc( (strlen(s) + sizeof(char) + 1 ), sizeof(char) );
			strcpy(trans_table[code].word , s);
			trans_table[code].word[strlen(s)]=Character;
			trans_table[code].word[strlen(s)+1]='\0';
			code++;
		}
		old_code = new_code;
	}
	fprintf(f_out,"\n");
	for ( i=0; i< code; i++)
		free(trans_table[i].word);
	free(trans_table);
	//free(b_buf);
	return 0;
} 
