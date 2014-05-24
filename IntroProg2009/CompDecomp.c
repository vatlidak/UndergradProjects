#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bit_io.h"
#include "CompDecomp.h"
#include "dict.h"
#define MAXLEN 1000

int compression(FILE* f_in, FILE* f_out,int maxbits)		/*συνάρτηση συμπίεσης*/
{								/*δίνονται τα ρεύματα εισόδου και εξόδου ως ορίσματα*/
	int i;
     	int nbits, BYTE, read_bytes, word_code;
	long int comp_bits;					
     	char Character; 
     	char STRING[MAXLEN];
     	bit_buf* b_buf;
	Treeptr Root;
	int code;
	
     	code=257;						/*ο πρώτος κωδικός μετά τους ASCHII και τον κωδικό εκκαθάρισης*/
     	Root=NULL;						/*η ρίζα του δυαδικού δέντρου*/
     	nbits = 9;
     	if ( (b_buf=bit_init(f_out)) == NULL )			/*δεσμεύω χώρο για το buffer με την bit_init*/
     	{							/*όπου θα γράφω*/
     		fprintf(stderr,"Out of Memory\n");
          	return -1;
     	}
	bit_write(maxbits-9,3,b_buf);					/* γράφω πρώτα τον αριθμό των maxbits */
     	i=0;
     	if ( (BYTE=fread(&STRING[i],sizeof(char),1,f_in)) != 1)		/*διαβάζω το πρώτο χαρακτηρα απο το ρεύμα εισόδου*/
     	{
           	fprintf(stderr,"file is empty\n");			/*και ελέγχω αν είναι άδειο*/
           	return -1;
     	}
	i++;
     	read_bytes = 1;						/*αριθμός των bytes που διαβάζονται για τον υπολογισμό του ποσοστού*/ 
	comp_bits=0;						/*αριθμός των bytes που συμπιέζονται για τον υπολογισμό του ποσοστού*/
	while ( feof(f_in) == 0 ) 				/*η feof επιστρέφει 0 όταν φτάσω στο τέλος του ρεύματος εισόδου*/
	{
     		BYTE=fread(&Character,sizeof(char),1,f_in);	/*διαβάζω ένα χαρακτήρα από το ρεύμα εισόδου*/
        	if ( BYTE != 1 )
     			break;
        	read_bytes+=BYTE;
          	STRING[i]=Character;				/*φυλάω το χαρακτήρα στο string*/
		i++;
          	STRING[i]='\0';
          	if ( treesearch(Root, STRING) == 0 )		/* εάν η καινουρια ακολουθία στο string δεν υπάρχει στο δέντρο*/
          	{						/* βγάζω στην έξοδο την παλιά ,χωρίς το νέο χαρακτήρα*/
           		STRING[i-1]='\0';
			if ( strlen(STRING)== 1 )		/*αν είναι χαρακτήρας, ο κωδικός είναι ο ASCHII*/
				bit_write(STRING[i-2],nbits,b_buf);
               		else					/*αλλιώς βρίσκω το κωδικό από το δέντρο*/
               		{
             			word_code = searchcode(Root, STRING);
              			bit_write(word_code,nbits,b_buf);
            		}
			comp_bits += nbits;
			if ( code == pow(2,nbits) )			/* αν το λεξικό είναι στα 2^nbits  */ 
			{					
				if (nbits != maxbits)			/* κάνω αναβάθμιση εφ'όσον μπορώ*/
					nbits++;
				if (8*read_bytes < comp_bits)		/* αν δε γίνεται επιτυχής συμπίεση*/
				{
					fprintf(stderr,"No compression\n");
					bit_write(256,nbits,b_buf);	/*βγάζω το κωδικό εκκαθάρισης με nbits*/
					deletetree(Root);		/*διαγράφω το δέντρο*/
					nbits = 9;			/*αρχικοποιώ ξανά*/
					comp_bits = 0;
					Root = NULL;
					code=257;
				}
			}
			if ( code != pow(2,maxbits) )			/* εάν το λεξικό δεν έχει γεμίσει*/
			{
				STRING[i-1]=Character;			/*προσθέτω την παλιά ακολουθία μαζί με το νέο χαρακτήρα*/
	          		STRING[i]='\0';				/*στο δέντρο*/
				addtree(&Root,STRING,code);
				code++;
			}
	     		STRING[0]=Character;			
         		STRING[1]='\0';
           		i=1;
     		}
	}
	if ( strlen(STRING)== 1 )				/*βγάζω στην έξοδο το τελευταίο κωδικό*/
 		bit_write(STRING[i-2],nbits,b_buf);
	else
    	{
         	word_code = searchcode(Root, STRING);
     	bit_write(word_code,nbits,b_buf);
    	}
	comp_bits+=nbits;					/*υπολογίζω το ποσοστό συμπίεσης*/
	per = ((float)( read_bytes*8-comp_bits)/ ((float )read_bytes*8))*100;
	bit_flush(b_buf);					/*αδειάζω το buffer στην έξοδο*/
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
	code = 257;					/*ο πρώτος κωδικός μετά τους ASCHII και τον κωδικό εκκαθάρισης*/
    	if ( (b_buf=bit_init(f_in)) == NULL )		/*δεσμεύω χώρο για το buffer με την bit_init*/
    	{						/*από όπου θα διαβάζω*/
    		fprintf(stderr,"Out of Memory\n");
         	return -1;
    	}
	x = bit_read( 3, b_buf );			/*τα τρία πρώτα bits μου δίνουν το maxbits*/
	maxbits=x+9;

	trans_table = calloc ( pow(2,maxbits) , sizeof(transcode) );	/*δεσμεύω χώρο για τον πίνακα μετάφρασης*/
	for ( i=0; i<=255; i++)						/*οι πρώτες 255 θέσεις είναι οι ASCHII κωδικοί*/
	{								/*που μεταφράζονται σε χαρακτήρες*/
		trans_table[i].code = i;
		if ( (trans_table[i].word=calloc(1,sizeof(char))) == NULL ){
			fprintf(stderr,"Malloc error\n");
			return -1;
		}
		trans_table[i].word[0]=i;
	}
	trans_table[256].code = 256;				/*ο 256 είναι ο κωδικός εκκαθάρισης*/
	for(i = 257; i<(int)pow(2,maxbits); i++)		/*ο υπόλοιπος πίνακας αρχικοπποιείται με -1 σαν κωδικό*/
		trans_table[i].code = -1;
 	old_code = bit_read( nbits, b_buf );			/*διαβάζω το πρώτο κωδικό*/
	sprintf(&Character,"%c",old_code);			/*τον κρατάω στο char*/
	fprintf(f_out,"%c",Character);				/*και βγάζω τη μετάφραση του στην έξοδο*/
	while ( (new_code = bit_read ( nbits, b_buf )) != (-2) )	/*διαβάζω καινούριο κωδικό από την έξοδο*/
	{
		STRING[0]='\0';
		if ( new_code == (-1) )				
			fprintf(stderr,"Reading error\n");
		if ( new_code == trans_table[new_code].code )   /* αν υπάρχει στον πίνακα μετάφρασης*/
		{						/*βάζω τη μετάφραση του στο string*/
			strcpy ( STRING , trans_table[new_code].word );
		}
		else						/* αν δεν υπάρχει βάζω στο string τη μετάφραση του */
		{						/*παλιού κωδικού και προσ8ετω το char*/
			strcpy ( STRING , trans_table[old_code].word );
			STRING[strlen(STRING)] = Character;
			STRING[strlen(STRING)+1] = '\0';
		}
		fprintf(f_out,"%s",STRING);			/*βγάζω στην έξοδο τη μετάφραση του string*/
		Character=STRING[0];				/*δίνω στο char το πρωτο χαρακτήρα του string*/	
		if ( new_code == 256)				/*ελέγχω αν πρόκειται για το κωδικό εκκαθάρισης*/
		{						/*αν ναι αρχικοποιώ πάλι το πινακά μου*/
			nbits = 9;
			code = 257;
			for(i = 257; i<(int)pow(2,maxbits); i++)
				trans_table[i].code = -1;
		}	
		if ( code == (int)pow(2,nbits)-1 && nbits<maxbits )	
			nbits++;
		if ( code != (int)pow(2,maxbits) )		/* αν ο πίνακας χωρά κ άλλα στοιχεία*/
		{
			trans_table[code].code = code;		/*προσθέτω το παλιό κωδικό και το char στο πίνακα*/
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
