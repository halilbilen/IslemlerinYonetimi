#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// Halil Ýbrahim Bilen - 160204059  - BLG201_Odev_2 
int a,c,h,s;
char islemCalis[100],Cdurum;
int Cruc,yap=0;
struct askii{
	char Aislem[10];
	char Adurum;
	int Aruchan;
	struct askii *sonraki;
};
struct askii *Ailk=NULL;
struct askii *Ason=NULL;
struct askii *temp1;
struct sons{
	char Sislem[10];
	char Sdurum;
	int Sruchan;
	struct sons *sonraki;
};
struct sons *Silk=NULL;
struct sons *Sson=NULL;
struct sons *temp2;
struct hazirr{
	char Hislem[10];
	char Hdurum;
	int Hruchan;
	struct hazirr *sonraki;
};
struct hazirr *Hilk=NULL;
struct hazirr *Hson=NULL;
struct hazirr *temp3;
void oku()
{
	FILE *oku;
	oku=fopen("islemler.txt","r");
	char islemad[100],durum;
	int ruc;
	while(!feof(oku))
	{
		fscanf(oku,"%s  %c   %d\n",&islemad,&durum,&ruc);
		if(durum=='H')
		{
			hazir(islemad,durum,ruc);
		}
		else if(durum=='A')
		{
			aski(yap,islemad,durum,ruc);
		}
		else if(durum=='C')
		{
			c++;
			strcpy(islemCalis,islemad);
			Cdurum=durum;
			Cruc=ruc;
		}
		else if(durum=='S')
		{
			son(islemad,durum,ruc);
		}
		else
		{
			h=0;
			a=0;
			c=0;
			s=0;
		}
	}
	if(h==0&&a==0&&c==0&&s==0)
	{
		printf("Dosya bos");
		exit(1);
	}
	else
	{
		printf("islemler.txt den veri okundu.\n");
	}
}
int main()
{
	oku();
	struct hazirr *ara;
	struct askii *ara2;
	printf("\n");
	yazdir();
	printf("\n");
	printf("AKTIF KOMUTLAR 'K' - 'B' - 'R' - 'X'\n");
	printf("\n");
	char x[10],secim[10];
	int i;
	while(1)
	{
		printf(">>>");
		scanf("%s",&secim);
		if(strcmp(secim,"K")==0)
		{
			ara=Hilk;
			ara2=Ailk;
			if(Hilk==NULL && Ailk==NULL&& strcmp(islemCalis,"")==0)
			{
				printf("Tum islemler sonlandirilmistir\n");
				exit(1);
			}
			printf(">");
			scanf("%s",&x);
			while(ara!=NULL)
			{
				if(strcmp(ara->Hislem,x)==0)
				{
					yap=1;
					son(ara->Hislem,ara->Hdurum,ara->Hruchan);
			        hazirsil(yap,x);
			        yazdir();
				}
				ara=ara->sonraki;
		    }
				while(ara2!=NULL)
				{
					if(strcmp(ara2->Aislem,x)==0)
					{
						yap=1;
						son(ara2->Aislem,ara2->Adurum,ara2->Aruchan);
						askisil(yap,x);
						yazdir();
					}
					else
					{
						if(strcmp(islemCalis,x)==0)
						{
							son(islemCalis,Cdurum,Cruc);
							strcpy(islemCalis,"");
							yazdir();
							printf("Calisan islem kalmamistir calistirmak icin R \n");
						}
					}
				    ara2=ara2->sonraki;
				}
		}
		else if(strcmp(secim,"B")==0)
		{
			yap=1;
			if(strcmp(islemCalis,"")!=0)
			{
				aski(yap,islemCalis,Cdurum,Cruc);
			    hazirsira();
			    yazdir();
			}
			else
			{
				printf("Calisan islem yoktur\n");
			}
		}
		else if(strcmp(secim,"R")==0)
		{
			if(strcmp(islemCalis,"")==0)
			{
				printf("Calisan islem yoktur\n");
				printf("Hazir bekleyenlerden calistiriliyor ...\n");;
			}
			else
			{
				printf("%s tamamlanmistir\n",islemCalis);
			}
			hazirsira();
			yazdir();
		}
		else if(strcmp(secim,"X")==0)
		{
			if(strcmp(islemCalis,"")!=0)
			{
				printf("%s tamamlanmistir\n",islemCalis);
				strcpy(islemCalis,"");
				c--;
			}
			while(h!=0)
			{
				hazirsira();
				printf("%s tamamlanmistir\n",islemCalis);
				strcpy(islemCalis,"");
			}
			temp1=Ailk;
			while(a!=0)
			{
				yap=1;
				son(temp1->Aislem,temp1->Adurum,temp1->Aruchan);
				askisil(yap,temp1->Aislem);
				temp1=temp1->sonraki;
			}
			yazdir();
			exit(1);
		}
		else
		{
			printf("Farkli bir komut girdiniz program kapatiliyor ...\n");
			exit(1);
		}
	}
	return 0;
}
void hazirsira()
{
	struct hazirr *temp;
	int kucuk;
	temp=Hilk;
	if(temp==NULL)
	{
		printf("Hazirda bekleyen islem yoktur\n");
		strcpy(islemCalis,"");
		return;
	}
	kucuk=temp->Hruchan;
	while(temp!=NULL)
	{
		if(kucuk>temp->Hruchan)
		{
			kucuk=temp->Hruchan;
		}
		temp=temp->sonraki;
	}
	konum(kucuk);
	printf("%s calistirildi\n",islemCalis);
}
void konum(int kucuk)
{
	struct hazirr *temp99;
	temp99=Hilk;
	while(temp99!=NULL)
	{
		if(kucuk==temp99->Hruchan)
		{
			strcpy(islemCalis,temp99->Hislem);
			Cdurum=temp99->Hdurum;
			Cruc=temp99->Hruchan;
			yap=0;
			hazirsil(yap,temp99->Hislem);
			return;
		}
		temp99=temp99->sonraki;
	}
}
void hazirsil(int yap,char x[])
{
	struct hazirr *g;
	struct hazirr *onceki=Hilk;
	if(Hilk==NULL)
	{
		printf("Hazirda bekleyen islem yoktur\n");
		return;
	}
	if(yap==1)
	{
		printf("%s sonlandirilmistir \n",x);
	}
	g=onceki->sonraki;
	if(strcmp(Hilk->Hislem,x)==0)
	{
		Hilk=Hilk->sonraki;
	}
	else
	{
		while(strcmp(g->Hislem,x)!=0)
		{
			onceki=g;
			g=g->sonraki;
		}
		onceki->sonraki=g->sonraki;
	}
	h--;
}
void askisil(int yap,char x[])
{
	struct askii *g;
	struct askii *onceki=Ailk;
	if(Ailk==NULL)
	{
		printf("Askida islem yoktur\n");
		return;
	}
	if(yap==1)
	{
		printf("%s sonlandirilmistir \n",x);
	}
	g=onceki->sonraki;
	if(strcmp(Ailk->Aislem,x)==0)
	{
		Ailk=Ailk->sonraki;
	}
	else
	{
		while(strcmp(g->Aislem,x)!=0)
		{
			onceki=g;
			g=g->sonraki;
		}
		onceki->sonraki=g->sonraki;
	}
	a--;
}
void hazir(char islemad[],char durum,int ruc)
{
	struct hazirr *ekleh;
	ekleh=(struct hazirr*)malloc(sizeof(struct hazirr));
	strcpy(ekleh->Hislem,islemad);
	ekleh->Hdurum=durum;
	ekleh->Hruchan=ruc;
	ekleh->sonraki=NULL;
	h++;
	if(Hilk==NULL)
	{
		Hilk=ekleh;
		Hson=Hilk;
	}
	else
	{
		Hson->sonraki=ekleh;
		Hson=Hson->sonraki;
	}
}
void son(char islemad[],char durum,int ruc)
{
	struct sons *ekles;
	ekles=(struct sons*)malloc(sizeof(struct sons));
	strcpy(ekles->Sislem,islemad);
	ekles->Sdurum=durum;
	ekles->Sruchan=ruc;
	ekles->sonraki=NULL;
	s++;
	if(Silk==NULL)
	{
		Silk=ekles;
		Sson=Silk;
	}
	else
	{
		Sson->sonraki=ekles;
		Sson=Sson->sonraki;
	}
}
void aski(int yap,char islemad[],char durum,int ruc)
{
	struct askii *eklea;
	eklea=(struct askii*)malloc(sizeof(struct askii));
	strcpy(eklea->Aislem,islemad);
	eklea->Adurum=durum;
	eklea->Aruchan=ruc;
	eklea->sonraki=NULL;
	a++;
	if(Ailk==NULL)
	{
		Ailk=eklea;
		Ason=Ailk;
	}
	else
	{
		Ason->sonraki=eklea;
		Ason=Ason->sonraki;
	}
	if(yap==1)
	{
		printf("%s askiya alinmistir\n",eklea->Aislem);
	}
}
void yazdir()
{
	printf("\n");
	struct hazirr *temp33=NULL;
	struct caliss *temp22=NULL;
	struct askii *temp11=NULL;
	struct sons *temp44=NULL;
	temp33=Hilk;
	printf("Hazir=");
	while(temp33!=NULL)
	{
		printf("%s->",temp33->Hislem);
		temp33=temp33->sonraki;
	}
	printf("\n");
	printf("Calisan=");
	printf("%s",islemCalis);
	printf("\n");
	temp11=Ailk;
	printf("Askida=");
	while(temp11!=NULL)
	{
		printf("%s->",temp11->Aislem);
		temp11=temp11->sonraki;
	}
	printf("\n");
	temp44=Silk;
	printf("Sonlandirilmis=");
	while(temp44!=NULL)
	{
		printf("%s->",temp44->Sislem);
		temp44=temp44->sonraki;
	}
	printf("\n");
}
